#include "Entity.h"
#include "Shape.h"
#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>

using namespace glm;

//constructor
Entity::Entity()
{

}

Entity::Entity(Shape* shape, float startPosX, float startPosY, float posChangeX, float posChangeY, float scaleX, float scaleY, float scaleXChange,
	float scaleYChange, float rotationAmountStart, float rotationAmountChange)
{
	this->startPosX = startPosX;
	this->startPosY = startPosY;
	this->posChangeX = posChangeX;
	this->posChangeY = posChangeY;
	this->scaleX = scaleX;
	this->scaleY = scaleY;
	this->scaleXChange = scaleXChange;
	this->scaleYChange = scaleYChange;
	this->rotationAmountStart = rotationAmountStart;
	this->rotationAmountChange = rotationAmountChange;
	vec3 force = vec3(0,0,0);
	vec3 velocity = vec3(0,0,0);
	//vec3 goDown = vec3(0, 10, 0);
	posVec = vec3(startPosX, startPosY, 0);
	scaleVec = vec3(scaleX, scaleY, 1);
	rotAxis = vec3(0, 1, 0);
	curRotAmount = rotationAmountStart;


}

//generic update method
void Entity::Update(float currentTime)
{
	vec3 friction = vec3(velocity.x * -1 / 32, velocity.y * -1/32, 0);
	this->addForce(friction);
	this->addForce(vec3(0,-0.2,0));
	velocity += force * currentTime ;

	posVec += velocity * currentTime;
	force = vec3(0, 0, 0);
	
	float area = 3.14 * 0.3 * 0.3;

	if (posVec.y - area <= -1)
	{
		velocity.y *= -0.9f;
	}
	if (posVec.y + area >= 1)
	{
		velocity.y *= -1.0f;
	}
	if (posVec.x + area >= 1)
	{
		velocity.x *= -1.0f;
	}
	if (posVec.x - area <= -1)
	{
		velocity.x *= -1.0f;
	}
	//posVec.x += posChangeX *currentTime;
	//posVec.y += posChangeY * currentTime;

	//scaleVec.x += scaleXChange;
	//scaleVec.y += scaleYChange;

	curRotAmount += rotationAmountChange;
}


//allows for setting of x and y pos
void Entity::setPosition(float xPos, float yPos)
{
	this->posVec.x = xPos;
	this->posVec.y = yPos;
	float rando = rand() * 0.00001;
	int sign = rand() % 2;
	if (sign == 1)
	{
		rando *= -1;
	}

	float rando2 = rand() * 0.00001;
	sign = rand() % 2;
	if (sign == 1)
	{
		rando2 *= -1;
	}

	float rando3 = rand() * 0.000001;
	sign = rand() % 2;
	if (sign == 1)
	{
		rando3 *= -1;
	}

	this->rotationAmountChange = rando3;

	this->velocity = vec3(rando, rando2, 0);

}

//allows for setting the x and y scale
void Entity::setScale(float xScale, float yScale)
{
	this->scaleVec.x = xScale;
	this->scaleVec.y = yScale;
}

//allows for setting the Shape pointer
void Entity::setShape(Shape* shape)
{
	this->shape = shape;
}

//returns yPos
float Entity::getPosY()
{
	return posVec.y;
}

//returns xPos
float Entity::getPosX()
{
	return posVec.x;
}

void Entity::addForce(vec3 force)
{
	this->force += force;
}

//calculates world matrix, then utilizes Shape class's draw method
void Entity::Draw()
{
	/*
	mat4 transMat = translate(posVec);
	mat4 scaleMat = scale(scaleVec);
	mat4 rotateMat = rotate(curRotAmount, rotAxis);

	mat4 worldMatrix = transMat * scaleMat * rotateMat;
	*/
	//shape->Draw(posVec, scaleVec, rotAxis, curRotAmount);
}

Entity::~Entity(void)
{
}