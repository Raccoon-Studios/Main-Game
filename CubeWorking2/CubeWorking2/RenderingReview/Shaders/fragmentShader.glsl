#version 430

in vec4 vertColor;
in vec3 fragPos;
in vec3 fragNorm;


uniform sampler2D uniformTex;
in vec2 fragTexUV;

void main()
{
	vec3 lightDir = vec3(0,0,1);
	float lamb = max(dot(lightDir,fragNorm),0);
	vec3 viewDir = normalize(-fragPos);
	vec3 halfDir = normalize(lightDir + viewDir);
	float specAngle = max(dot(halfDir, fragNorm),0);
	float specular = pow(specAngle, 16.0);
	float light = .1 + .6 *lamb + .3*specular;
	vec4 color = texture(uniformTex, fragTexUV);
	gl_FragColor = vec4(color.rgb * light, 1);
}