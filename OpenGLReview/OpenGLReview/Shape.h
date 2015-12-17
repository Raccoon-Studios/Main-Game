#pragma once

#include <glew.h>
#include "ShaderHelper.h"
#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>

#include <iostream>
#include <fstream>
#include <vector>

#include "Obb.h"

using namespace std;
class Shape
{

public:
	GLuint vertexBufferObject;
	GLuint vertexArrayObject;
	GLuint shaderProgramIndex;
	
	GLint offsetUniformVarLoc;
	GLint scaleUniformVarLoc;

	vector<glm::vec3> shapeVertices;
	vector<glm::vec2> shapeUVs;
	vector<glm::vec3> shapeNormals;

	int numVertices;
	glm::vec3 GetPos();
	glm::vec3 GetScale();
	glm::vec3 GetVel();
	glm::vec3 GetAccel();
	glm::vec3 GetRotAxis();
	float GetRotAmnt();
	Obb * GetOBB();

	void SetPos(glm::vec3 newPos);
	void SetScale(glm::vec3 scaleVec);
	void SetAccel(glm::vec3 accel);
	void SetRotAxis(glm::vec3 rotAxis);
	void SetRotAmnt(float rotAmnt);
	void SetVel(glm::vec3 newVel);


	Shape(vector<glm::vec3> vertices, int numVertices, int numComponents, vector<unsigned int > vertexIndices, 
		vector<unsigned int > uvIndices, vector<unsigned int > normalIndices,  vector<glm::vec2> uvs, vector<glm::vec3> normals, GLuint shaderProgramIndex);
	~Shape(void);
	void Update();
	//void Draw(glm::vec2 position, float xScale, float yScale);
	void Draw(glm::vec3 currentPosition, glm::vec3 scale, glm::vec3 rotationAxis, float rotationAmount, glm::mat4* camera, glm::mat4* viewMatrix);
	void Draw(glm::mat4 worldMatrix);


private:
	Obb obb;
	glm::vec3 vel;
	glm::vec3 accel;
	glm::vec3 currentPosition;
	glm::vec3 scale;
	glm::vec3 rotationAxis;
	float es [3];
	glm::vec4 us[3];
	float rotationAmount;

};

