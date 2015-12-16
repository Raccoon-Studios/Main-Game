#include "Shape.h"
#include <glew.h>
//#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>
#include <vector>
#include "ShaderHelper.h"

#include<iostream>
#include<fstream>
#include<SOIL.h>



#pragma once
using namespace std;

GLuint vertexBufferObject;
GLuint vertexArrayObject;
GLuint shaderProgramIndex;

glm::vec3 currentPosition;
glm::vec3 scaleVec;
glm::vec3 rotationAxis;
float rotationAmount;

GLint offsetUniformVarLoc;
GLint scaleUniformVarLoc;
GLint worldMatUniformVarLoc;
GLint viewMatUnifromVarLoc;

GLuint texID;
GLuint ebuffer;
//GLushort elements[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11 };

int numElements;
int numVertices;

vector <unsigned int> indices;
vector <GLfloat> faces;

Shape::Shape(vector<glm::vec3> vertices, int numVertices, int numComponents, vector<unsigned int > vertexIndices, vector<unsigned int > uvIndices, vector<unsigned int > normalIndices, vector<glm::vec2> uvs, vector<glm::vec3> normals, GLuint shaderProgramIndex)
{
	this->shaderProgramIndex = shaderProgramIndex;
	this->numVertices = vertices.size() * sizeof(glm:: vec3);
	this->shapeVertices = vertices;
	this->shapeUVs = uvs;
	this->shapeNormals = normals;

	for (int i = 0; i < vertexIndices.size(); i++)
	{
		faces.push_back(vertices[i].x);
		faces.push_back(vertices[i].y);
		faces.push_back(vertices[i].z);

		faces.push_back(uvs[i].x);
		faces.push_back(uvs[i].y);

		faces.push_back(normals[i].x);
		faces.push_back(normals[i].y);
		faces.push_back(normals[i].z);


		indices.push_back(i);
	}

	//indices = vertexIndices;
	texID = SOIL_load_OGL_texture("archer.jpg", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
	glBindTexture(GL_TEXTURE_2D, texID);
	glGenVertexArrays(1, &vertexArrayObject);
	glBindVertexArray(vertexArrayObject);

	glGenBuffers(1, &vertexBufferObject);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
	
	/*
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, (sizeof(GL_FLOAT) * 3), 0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(GL_FLOAT) * 3, (void*)(sizeof(GL_FLOAT) * 3));
	*/

	
	glBufferData(GL_ARRAY_BUFFER, faces.size() * sizeof(GL_FLOAT), &faces[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, (sizeof(GL_FLOAT) * 8 ), 0);
	
	glEnableVertexAttribArray(0);
	//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, (sizeof(GL_FLOAT) * 5), (void*)(sizeof(GL_FLOAT) * 2));
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, (sizeof(GL_FLOAT) * 8), (void*)(sizeof(GL_FLOAT) * 3));
	

	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, (sizeof(GL_FLOAT) * 8), (void*)(sizeof(GL_FLOAT) * 5));


	glEnableVertexAttribArray(2);
	
	
	glGenBuffers(1, &ebuffer);
	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GL_UNSIGNED_INT), &indices[0], GL_STATIC_DRAW);
	

	currentPosition.x = 0.0f;
	currentPosition.y = 0.0f;


	scale = glm::vec3(0.25, 0.25, 0.25);

	scaleVec = glm::vec3(1, 1, 1);
	rotationAxis = glm::vec3(0, 1, 0);
	rotationAmount = 0.0f;

	offsetUniformVarLoc = glGetUniformLocation(shaderProgramIndex, "offset");
	scaleUniformVarLoc = glGetUniformLocation(shaderProgramIndex, "scale");
	worldMatUniformVarLoc = glGetUniformLocation(shaderProgramIndex, "worldMatrix");

	es[0] = scale.x / 2;
	es[1] = scale.y / 2;
	es[2] = scale.z / 2;

	us[0] = glm::vec4(1.0, 0, 0, 0);
	us[1] = glm::vec4(0, 1.0, 0, 0);
	us[2] = glm::vec4(0, 0, 1.0, 0);


	obb = Obb(currentPosition, us, es);

}


Shape::~Shape()
{
	glDeleteVertexArrays(sizeof(vertexArrayObject), &vertexArrayObject);
	glDeleteBufferRegion(vertexBufferObject);
}

void Shape::Draw(float x, float y, float xScale, float yScale)
{

}

void Shape::Draw(glm::vec3 position, glm::vec3 scale, glm::vec3 rotationaxis, float rotationAmount, glm::mat4* camera, glm::mat4* view)
{
	glm::mat4 transMat = glm::translate(position);
	glm::mat4 scaleMat = glm::scale(scale);
	glm::mat4 rotateMat = glm::rotate(rotationAmount, rotationAxis);

	glm::mat4 worldMatrix = transMat * scaleMat * rotateMat;
	
	worldMatrix = *camera * worldMatrix;
	glProgramUniformMatrix4fv(shaderProgramIndex, worldMatUniformVarLoc, 1, GL_FALSE, &worldMatrix[0][0]);

	
	glBindVertexArray(vertexArrayObject);

	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebuffer);
	//glBindTexture(GL_TEXTURE_2D, texID);
	//glBindVertexArray(vertexArrayObject);
	//glDrawArrays(GL_TRIANGLES, 0, totIndices.size() * sizeof(GL_FLOAT));
	//glDrawArrays(GL_TRIANGLES, 0, numVertices);

	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, (void *)0);
}

void Shape::Update()
{
	vel += accel;
	currentPosition += vel;

	accel = glm::vec3(0, 0, 0);
	obb.SetCenter(currentPosition);
}

glm::vec3 Shape::GetAccel()
{
	return accel;
}

void Shape::SetAccel(glm::vec3 newAccel)
{
	accel = newAccel;
}

glm::vec3 Shape::GetVel()
{
	return vel;
}

glm::vec3 Shape::GetScale()
{
	return scale;
}

void Shape::SetScale(glm::vec3 newScale)
{
	scale = newScale;

	es[0] = scale.x / 2;
	es[1] = scale.y / 2;
	es[2] = scale.z / 2;
	obb.SetWidths(es);
}

glm::vec3 Shape::GetRotAxis()
{
	return rotationAxis;
}

void Shape::SetRotAxis(glm::vec3 newRotAxis)
{
	rotationAxis = newRotAxis;
}

float Shape::GetRotAmnt()
{
	return rotationAmount;
}

glm::vec3 Shape::GetPos()
{
	return currentPosition;
}

Obb* Shape::GetOBB()
{
	return &obb;
}