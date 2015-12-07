#pragma once
#include "Shape.h"
#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>

using namespace glm;
class Entity
{
public:


	void Update(float currentTime);
	Entity();
	Entity(Shape* shape, float startPosX, float startPosY, float posChangeX, float posChangeY, float scaleX, float scaleY, float scaleXChange,
		float scaleYChange, float rotationAmountStart, float rotationAmountChange);
	void setPosition(float xPos, float yPos);
	void setScale(float xScale, float yScale);
	float getPosY();
	float getPosX();
	
	void Draw();
	void setShape(Shape* shape);
	~Entity(void);
private:
	void addForce(vec3 force);
	float startPosX;
	float startPosY;
	float posChangeX;
	float posChangeY;

	float scaleX;
	float scaleY;
	float scaleXChange;
	float scaleYChange;

	float rotationAmountStart;
	float rotationAmountChange;

	vec3 goDown;
	vec3 posVec;
	vec3 scaleVec;
	vec3 rotAxis;
	vec3 velocity;
	vec3 force;
	float curRotAmount;

	Shape* shape;
};