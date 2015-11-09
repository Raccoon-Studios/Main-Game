#pragma once
#include<glew.h>
#include<glfw3.h>
#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>
using namespace glm;
#include"ShaderHelpers.h"
class GameObject
{
public:
	GameObject(GLuint programIndex);
	~GameObject();
	void update(float dt);
	void draw();
	vec3 getPosition();
private:
	vec3 velocity;
	vec3 position;
	vec3 force;
	float rotationAngle;
	GLuint programIndex;
	float mass;
	vec3 angularV;
	void deflect();
};

