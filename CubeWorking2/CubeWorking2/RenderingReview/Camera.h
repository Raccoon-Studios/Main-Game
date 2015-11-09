#pragma once
#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>

using namespace glm;
class Camera
{
public:
	void turn(float dx, float dy);
	vec3 getLocation();
	vec3 getForward();
	vec3 getLookAt();
	vec3 getUp();
	vec3 getRight();
	vec3 pos;
	float yaw;
	float pitch;
	vec3 up;
	vec3 right;
	vec3 forward;
	Camera();
	~Camera();
};