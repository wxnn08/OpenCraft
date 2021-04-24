#version 410

in vec3 fragN;
in vec3 fragL;
in vec3 fragV;
in vec2 fragTexCoord;
in vec3 fragPObj;
in vec3 fragNObj;

uniform highp float time;

// Light properties
uniform vec4 Ia, Id, Is;

// Material properties
uniform vec4 Ka, Kd, Ks;
uniform float shininess;

// Diffuse texture sampler
uniform sampler2D diffuseTex;
uniform sampler2D noiseTex1;
uniform sampler2D noiseTex2;

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

float cartoonizeValue(float x) {
	float c;
	if(x < 0.4) {
		c = 0.0;
	} else if(x < 0.5){
		c = 0.2;
	} else if(x < 0.6){
		c = 0.5;
	} else if(x < 0.8){
		c = 0.7;
	} else {
		c = 0.95;
	}
	return c;
}

vec4 cartoonizeVec4(vec4 v) {
	v.x = cartoonizeValue(v.x);
	v.y = cartoonizeValue(v.y);
	v.z = cartoonizeValue(v.z);
	return v;
}

void main() {
	vec4 color;
	vec2 texCoord = fragTexCoord;
	color = BlinnPhong(fragN, fragL, fragV, texCoord);

	vec4 noiseColor1 = texture(noiseTex1, texCoord + time/2.0);
	vec4 noiseColor2 = texture(noiseTex1, texCoord - time/5.0);

	vec4 noiseColor = (noiseColor1 + noiseColor2) * 0.5;

	noiseColor = cartoonizeVec4(noiseColor);

	color = color + noiseColor;
	color[3] = 0.8;

	if (gl_FrontFacing) {
		outColor = color;
	} else {
		float i = (color.r + color.g + color.b) / 3.0;
		outColor = vec4(i, 0, 0, 1.0);
	}
}
