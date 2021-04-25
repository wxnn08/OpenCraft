#version 410

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 inNormal;
layout(location = 2) in vec2 inTexCoord;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projMatrix;
uniform mat3 normalMatrix;

uniform sampler2D noiseTex1;
uniform sampler2D noiseTex2;

uniform vec4 lightDirWorldSpace;
uniform highp float time;

out vec3 fragV;
out vec3 fragL;
out vec3 fragN;
out vec2 fragTexCoord;
out vec3 fragPObj;
out vec3 fragNObj;

void main() {

	vec2 uv = inTexCoord * 5.0f;
	vec3 newPos = inPosition;

	newPos.y = ((sin(time + uv.x*5000.0) + cos(time + uv.y*3000.0)) / 6.0);

	vec3 P = (viewMatrix * modelMatrix * vec4(newPos, 1.0)).xyz;
	vec3 N = normalMatrix * inNormal;
	vec3 L = -(viewMatrix * lightDirWorldSpace).xyz;

	fragL = L;
	fragV = -P;
	fragN = N;
	fragTexCoord = inTexCoord;
	fragPObj = newPos;
	fragNObj = inNormal;

	gl_Position = projMatrix * vec4(P, 1.0);
}
