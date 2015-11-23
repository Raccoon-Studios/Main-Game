#pragma once
#include "ShaderHelpers.h"
#include <vector>
#include <fstream>
#include <string>
#include<SOIL.h>

using namespace std;
using namespace glm;

class Object3d
{
public:
	std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;
	std::vector< unsigned short > vertices;
	std::vector< unsigned short > uvs;
	std::vector< unsigned short > normals;
	mat4 rotation;
	GLuint vao;
	GLuint texID;
	vec3 position;
	vec3 scale;
	char *filepath;
	Object3d(char *file);
	bool loadObj();
	void Draw(GLuint program, GLint wm, GLint pos, GLint scale1);
	void Rotate(float angle, float x, float y, float z);
	bool loadTex(const char *file);
	~Object3d();
};
