#include "GameObject.h"


GameObject::GameObject(GLuint programIndex)
{
	this->programIndex = programIndex;

	this->velocity = vec3(0, 0, 0);
	this->position = vec3(0, 0, 0);
	this->force = vec3(0, -3.0f, 0);
	this->angularV = vec3(0, 0, 0);
	this->mass = 5.0f;
	this->rotationAngle = 0;
}


GameObject::~GameObject()
{
}

vec3 GameObject::getPosition(){
	return this->position;
}
void GameObject::deflect(){
	//vec3 vNorm = surfaceNormal * dot(velocity, surfaceNormal);
	//velocity -= vNorm * 2.0f;
}

void GameObject::update(float dt){
	velocity += force * dt / mass;
	position += velocity * dt;
	force = vec3(0, 0, 0);

	force.y -= 5;
	velocity.y - +.98f;

	/*if (position.x <= -395){
		def
	}
	else if (position.x >= 395){

	}
	else if (position.y <= -395){

	}
	else if (position.y >= 395){

	}*/

	//w = v/r
	angularV = velocity / .5f;
	//rotationAngle += angularV * dt;
}

void GameObject::draw(){
	mat4 worldMatrix = translate(position) * scale(vec3(.5,.5,.5)) * rotate(rotationAngle, vec3(0,0,1));
	setShaderMatrix(programIndex, "worldMatrix", worldMatrix);
}
