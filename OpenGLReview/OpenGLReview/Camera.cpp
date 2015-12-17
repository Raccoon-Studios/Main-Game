#include "Camera.h"
#include <iostream>
#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>
using namespace glm;
using namespace std;

Camera::Camera()
{
	this->pos = vec3(-20.0f, 0.0f, 0.0f);
	this->up = vec3(0.0f, 1.0f, 0.0f);
	//this->right = 
	//this->forward = vec3(0.0f, 0.0f, 1.0f);
	this->yaw = 0;
	this->pitch = 0;
}


Camera::~Camera()
{
}

vec3 Camera::getForward()
{
	forward.x = cos(radians(yaw)) * cos(radians(pitch));
	forward.y = sin(radians(pitch));
	forward.z = sin(radians(yaw)) * cos(radians(pitch));
	forward = normalize(forward);
	
	return forward;
}

vec3 Camera:: getLocation()
{
	return pos;
}

vec3 Camera::getLookAt()
{
	vec3 lookAt = pos + forward;
	return lookAt;
}

vec3 Camera::getRight()
{
	right = normalize(cross(vec3(0, 1, 0), forward));
	return right;
}

vec3 Camera::getUp()
{
	up = cross(forward, right);
	return up;
}

 void Camera::turn(float dx, float dy)
{
	yaw -= dx;
	pitch += dy;
	if (pitch > 50)
	{
		pitch = 50;
	}

	if (pitch < -50)
	{
		pitch = -50;
	}
	
}