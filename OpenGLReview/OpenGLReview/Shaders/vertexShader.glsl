#version 430

layout(location = 0) in vec3 vecPos;
layout(location =1) in vec2 vecTexUV;
layout(location =2) in vec3 vecNorm;

out vec3 fragPos;
out vec3 fragNorm;

out vec2 fragTexUV;

uniform vec3 offset;
uniform vec3 scale;
uniform mat4 worldMatrix;

out vec4 vertColor;

void main()
{
	fragTexUV = vecTexUV;
	gl_Position = worldMatrix * vec4(vecPos, 1);
	fragPos = gl_Position.xyz;
	fragNorm = normalize(vecNorm);
}