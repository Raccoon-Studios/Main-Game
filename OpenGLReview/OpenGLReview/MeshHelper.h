#pragma once
#include <glew.h>
#include <string>
#include <vector>
#include <glm\glm.hpp>
using namespace std;
class MeshHelper
{
public:
	MeshHelper();
	~MeshHelper();

	//loads obj file containing mesh data
	string loadTextFile(const char* file, vector<glm::vec3> & out_vertices, vector <glm::vec2> & out_uvs, vector <glm::vec3> & out_normals, vector <unsigned int>& out_vertexIndices, vector <unsigned int>& out_uvIndices, vector <unsigned int>& out_normalIndices);

};

