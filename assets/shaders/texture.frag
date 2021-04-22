#version 410

in vec3 fragN;
in vec3 fragL;
in vec3 fragV;
in vec2 fragTexCoord;
in vec3 fragPObj;
in vec3 fragNObj;

uniform float time;

// Light properties
uniform vec4 Ia, Id, Is;

// Material properties
uniform vec4 Ka, Kd, Ks;
uniform float shininess;

// Diffuse texture sampler
uniform sampler2D diffuseTex;
uniform sampler2D noiseTex;

out vec4 outColor;

// Blinn-Phong reflection model
vec4 BlinnPhong(vec3 N, vec3 L, vec3 V, vec2 texCoord) {
	N = normalize(N);
	L = normalize(L);

	// Compute lambertian term
	float lambertian = max(dot(N, L), 0.0);

	// Compute specular term
	float specular = 0.0;
	if (lambertian > 0.0) {
		V = normalize(V);
		vec3 H = normalize(L + V);
		float angle = max(dot(H, N), 0.0);
		specular = pow(angle, shininess);
	}

	vec4 map_Kd = texture(diffuseTex, texCoord);
	vec4 map_Ka = map_Kd;

	vec4 diffuseColor = map_Kd * Kd * Id * lambertian;
	vec4 specularColor = Ks * Is * specular;
	vec4 ambientColor = map_Ka * Ka * Ia;

	return ambientColor + diffuseColor + specularColor;
}

float test(float x) {
	float c;
	if(x < 0.2) {
		c = 0.0;
	} else if(x < 0.5) {
		c = 0.5;
	} else if(x < 0.7) {
		c = 0.7;
	} else {
		c = 1.0;
	}
	return c;
}

void main() {
	vec4 color;
	vec2 texCoord = fragTexCoord;
	color = BlinnPhong(fragN, fragL, fragV, texCoord);

	vec4 noiseColor = texture(noiseTex, texCoord + time/30.0);
	noiseColor.x = test(noiseColor.x);
	noiseColor.y = test(noiseColor.y);
	noiseColor.z = test(noiseColor.z);

	color = color + noiseColor;

	if (gl_FrontFacing) {
		outColor = color;
	} else {
		float i = (color.r + color.g + color.b) / 3.0;
		outColor = vec4(i, 0, 0, 1.0);
	}
}
