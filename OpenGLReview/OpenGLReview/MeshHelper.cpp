#include "MeshHelper.h"
#include <glew.h>
#include <fstream>
#include <iostream>
#include <string>

#include <sstream>

using namespace std;

string wholeString;
MeshHelper::MeshHelper()
{
}


MeshHelper::~MeshHelper()
{
}

//vector<glm::vec3> & out_vertices, vector <glm:: vec2> & out_uvs, vector <glm :: vec3> & out_normals
string MeshHelper::loadTextFile(const char* file, vector<glm::vec3> & out_vertices, vector <glm::vec2> & out_uvs, vector <glm::vec3> & out_normals, vector <unsigned int>& out_vertexIndices, vector <unsigned int>& out_uvIndices, vector <unsigned int>& out_normalIndices)
{
	vector<unsigned int > vertexIndices, uvIndices, normalIndices;
	vector<glm::vec3> temp_vertices;
	vector<glm::vec2> temp_uvs;
	vector<glm::vec3> temp_normals;
	//opening file
	ifstream inFile(file, ios::in);
	if (!inFile.is_open()) return 0;

	//reading file
	string line;
	char firstChar;
	while (getline(inFile, line))
	{
		//determines line is not empty
		if (!line.empty())
		{
			firstChar = line.at(0);
		}

		//determining identifier of line
		if (firstChar == 'v')
		{
			char secondChar = line.at(1);
			if (secondChar == 'n')
			{
				glm::vec3 normal;
				istringstream myISS = istringstream(line);
				string subString;
				myISS >> subString;
				float subFloat;
				myISS >> subFloat;
				normal.x = subFloat;

				cout << subFloat << endl;

				myISS >> subFloat;
				normal.y = subFloat;
				cout << subFloat << endl;

				myISS >> subFloat;
				normal.z = subFloat;
				temp_normals.push_back(normal);
				cout << subFloat << endl;

			}
			if (secondChar == 't')
			{
				glm::vec2 uv;
				istringstream myISS = istringstream(line);
				string subString;
				myISS >> subString;
				float subFloat;
				myISS >> subFloat;
				uv.x = subFloat;
				cout << subFloat << endl;

				myISS >> subFloat;
				uv.y = subFloat;
				temp_uvs.push_back(uv);
				cout << subFloat << endl;

			}
			if (secondChar != 't' && secondChar != 'n')
			{
				glm::vec3 vertex;
				istringstream myISS = istringstream(line);
				string subString;
				myISS >> subString;
				float subFloat;
				myISS >> subFloat;
				vertex.x = subFloat;

				cout << subFloat << endl;

				myISS >> subFloat;
				vertex.y = subFloat;
				cout << subFloat << endl;

				myISS >> subFloat;
				vertex.z = subFloat;
				temp_vertices.push_back(vertex);
				cout << subFloat << endl;


			}
		}


		if (firstChar == 'f')
		{
			string space = " ";
			char copyLine[100];
			
			/*
			for (int i = 0; i < strlen(line); i++)
			{
				if (line.at(i) == '/')
				{
					//line.replace(i, 1, space);
				}
			}*/

			string vertex1, vertex2, vertex3;
			
			unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
			 
			istringstream myISS = istringstream(line);

			string subString;
			myISS >> subString;
			cout << subString << endl;

			int subInt;
			myISS >> subInt;
			vertexIndices.push_back(subInt);
			cout << subInt << endl;

			char char1;
			myISS >> char1;
		

			myISS >> subInt;
			uvIndices.push_back(subInt);
			cout << subInt << endl;

			myISS >> char1;
			

			myISS >> subInt;
			normalIndices.push_back(subInt);
			cout << subInt << endl;

			

			myISS >> subInt;
			vertexIndices.push_back(subInt);
			cout << subInt << endl;

			myISS >> char1;

			myISS >> subInt;
			uvIndices.push_back(subInt);
			cout << subInt << endl;

			myISS >> char1;
		

			myISS >> subInt;
			normalIndices.push_back(subInt);
			cout << subInt << endl;


			myISS >> subInt;
			vertexIndices.push_back(subInt);
			cout << subInt << endl;

			myISS >> char1;
	

			myISS >> subInt;
			uvIndices.push_back(subInt);
			cout << subInt << endl;

			myISS >> char1;
		

			myISS >> subInt;
			normalIndices.push_back(subInt);
			cout << subInt << endl;

			



		}

		

		//cout << firstChar << endl;
		cout << line << endl;
		wholeString.append(line);
		line.clear();
	}

	for (unsigned int i = 0; i < vertexIndices.size(); i++)
	{
		unsigned int vertexIndex = vertexIndices[i];
		out_vertexIndices.push_back(vertexIndex - 1);
		glm::vec3 vertex = temp_vertices[vertexIndex - 1];
		out_vertices.push_back(vertex);
	}

	for (unsigned int i = 0; i < uvIndices.size(); i++)
	{
		unsigned int uvIndex = uvIndices[i];
		out_uvIndices.push_back(uvIndex - 1);
		glm::vec2 uv = temp_uvs[uvIndex - 1];
		out_uvs.push_back(uv);
	}

	for (unsigned int i = 0; i < normalIndices.size(); i++)
	{
		unsigned int normalIndex = normalIndices[i];
		out_normalIndices.push_back(normalIndex - 1);
		glm::vec3 normal = temp_normals[normalIndex - 1];
		out_normals.push_back(normal);
	}

	return wholeString;
}
