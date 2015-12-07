#pragma once

#include <glew.h>
#include "ShaderHelper.h"
#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>

#include <iostream>
#include <fstream>
#include <vector>
using namespace std;
class Shape
{

public:
	GLuint vertexBufferObject;
	GLuint vertexArrayObject;
	GLuint shaderProgramIndex;
	glm:: vec3 currentPosition;
	glm:: vec3 scale;
	glm::vec3 rotationAxis;
	float rotationAmount;
	GLint offsetUniformVarLoc;
	GLint scaleUniformVarLoc;

	vector<glm::vec3> shapeVertices;
	vector<glm::vec2> shapeUVs;
	vector<glm::vec3> shapeNormals;

	int numVertices;

	Shape(vector<glm::vec3> vertices, int numVertices, int numComponents, vector<unsigned int > vertexIndices, 
		vector<unsigned int > uvIndices, vector<unsigned int > normalIndices,  vector<glm::vec2> uvs, vector<glm::vec3> normals, GLuint shaderProgramIndex);
	~Shape(void);

	void Draw(float x, float y, float xScale, float yScale);
	//void Draw(glm::vec2 position, float xScale, float yScale);
	void Draw(glm::vec3 currentPosition, glm::vec3 scale, glm::vec3 rotationAxis, float rotationAmount, glm::mat4* camera, glm::mat4* viewMatrix);
	void Draw(glm::mat4 worldMatrix);


};

