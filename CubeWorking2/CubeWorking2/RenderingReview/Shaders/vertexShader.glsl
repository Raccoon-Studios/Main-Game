#version 430

layout(location = 0)in vec3 position;
layout(location = 2) in vec2 vecTexUV;
layout(location = 1) in vec3 color;
layout(location = 3) in vec3 vecNorm;
out vec3 fragPos;
out vec3 fragNorm;
out vec4 vertColor;
out vec2 fragTexUV;
uniform mat4 worldMatrix;
uniform mat4 cameraMatrix;


void main()
{
	fragTexUV = vecTexUV;
	gl_Position = cameraMatrix * worldMatrix * vec4(position, 1);
	
	fragPos = gl_Position.xyz;
	fragNorm = normalize(vecNorm);
}