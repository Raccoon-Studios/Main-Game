#include "Object3d.h"


Object3d::Object3d(char *file)
{
	filepath = file;
	//rotation = glm::rotate(0.0f, vec3(.5, .5, .5));
}

bool Object3d::loadObj()
{
	ifstream file(filepath);
	if (!file.is_open())
	{
		printf("Can't open file!\n");
		return false;
	}

	std::vector<GLfloat> temp_vertices;
	std::vector<GLfloat> temp_uvs;
	std::vector<GLfloat> temp_normals;

	string lineHeader;
	while (file >> lineHeader)
	{

		// else : parse lineHeader
		if (lineHeader == "v")
		{
			glm::vec3 vertex;
			file >> vertex.x;
			file >> vertex.y;
			file >> vertex.z;
			cout << vertex.x << "," << vertex.y << "," << vertex.z << endl;
			//fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
			temp_vertices.push_back(vertex.x);
			temp_vertices.push_back(vertex.y);
			temp_vertices.push_back(vertex.z);
		}
		else if (lineHeader == "vt")
		{
			glm::vec2 uv;
			file >> uv.x;
			file >> uv.y;
			//fscanf(file, "%f %f\n", &uv.x, &uv.y);
			temp_uvs.push_back(uv.x);
			temp_uvs.push_back(uv.y);
		}
		else if (lineHeader == "vn")
		{
			glm::vec3 normal;
			file >> normal.x;
			file >> normal.y;
			file >> normal.z;
			//fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
			temp_normals.push_back(normal.x);
			temp_normals.push_back(normal.y);
			temp_normals.push_back(normal.z);
		}
		else if (lineHeader == "f")
		{
			std::string vertex1, vertex2, vertex3;
			unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
			file >> vertex1;
			file >> vertex2;
			file >> vertex3;

			string temp1 = "", temp2 = "", temp3 = "";
			int j;
			for (unsigned int i = 0; i < vertex1.length(); i++)
			{
				if (vertex1.at(i) != '/')
					temp1 += vertex1.at(i);
				else
				{
					j = i;
					break;
				}
			}
			for (unsigned int i = j + 1; i < vertex1.length(); i++)
			{
				if (vertex1.at(i) != '/')
					temp2 += vertex1.at(i);
				else
				{
					j = i;
					break;
				}
			}
			for (unsigned int i = j + 1; i < vertex1.length(); i++)
			{
				if (vertex1.at(i) != '\0')
					temp3 += vertex1.at(i);
				else
					break;
			}

			vertexIndex[0] = stoi(temp1);
			uvIndex[0] = stoi(temp2);
			normalIndex[0] = stoi(temp3);

			temp1 = ""; temp2 = ""; temp3 = "";
			for (unsigned int i = 0; i < vertex2.length(); i++)
			{
				if (vertex2.at(i) != '/')
					temp1 += vertex2.at(i);
				else
				{
					j = i;
					break;
				}
			}
			for (unsigned int i = j + 1; i < vertex2.length(); i++)
			{
				if (vertex2.at(i) != '/')
					temp2 += vertex2.at(i);
				else
				{
					j = i;
					break;
				}
			}
			for (unsigned int i = j + 1; i < vertex2.length(); i++)
			{
				if (vertex2.at(i) != '\0')
					temp3 += vertex2.at(i);
				else
					break;
			}

			vertexIndex[1] = stoi(temp1);
			uvIndex[1] = stoi(temp2);
			normalIndex[1] = stoi(temp3);

			temp1 = ""; temp2 = ""; temp3 = "";
			for (unsigned int i = 0; i < vertex3.length(); i++)
			{
				if (vertex3.at(i) != '/')
					temp1 += vertex3.at(i);
				else
				{
					j = i;
					break;
				}
			}
			for (unsigned int i = j + 1; i < vertex3.length(); i++)
			{
				if (vertex3.at(i) != '/')
					temp2 += vertex3.at(i);
				else
				{
					j = i;
					break;
				}
			}
			for (unsigned int i = j + 1; i < vertex3.length(); i++)
			{
				if (vertex3.at(i) != '\0')
					temp3 += vertex3.at(i);
				else
					break;
			}

			vertexIndex[2] = stoi(temp1);
			uvIndex[2] = stoi(temp2);
			normalIndex[2] = stoi(temp3);
			//sscanf(vertex1.c_str(), "%d/%d/%d ", &vertexIndex[0], &uvIndex[0], &normalIndex[0]);
			//int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
			//if (matches != 9){
			//printf("File can't be read :(\n");
			//return false;
			//}
			vertexIndices.push_back(vertexIndex[0]);
			vertexIndices.push_back(vertexIndex[1]);
			vertexIndices.push_back(vertexIndex[2]);
			uvIndices.push_back(uvIndex[0]);
			uvIndices.push_back(uvIndex[1]);
			uvIndices.push_back(uvIndex[2]);
			normalIndices.push_back(normalIndex[0]);
			normalIndices.push_back(normalIndex[1]);
			normalIndices.push_back(normalIndex[2]);
		}
	}

	for (unsigned short i = 0; i < vertexIndices.size(); i++)
	{
		unsigned short vertexIndex = vertexIndices[i];
		//glm::vec3 vertex = temp_vertices[vertexIndex - 1];
		unsigned short vertex = vertexIndex - 1;
		vertices.push_back(vertex);
	}

	for (unsigned int i = 0; i < uvIndices.size(); i++)
	{
		unsigned short uvIndex = uvIndices[i];
		unsigned short uv = uvIndex - 1;
		uvs.push_back(uv);
	}

	for (unsigned int i = 0; i < normalIndices.size(); i++)
	{
		unsigned short normalIndex = normalIndices[i];
		unsigned short normal = normalIndex - 1;
		normals.push_back(normal);
	}

	file.close();
	for (unsigned int i = 0; i < vertices.size(); i++)
		cout << vertices[i] << ", ";
	cout << endl;

	for (unsigned int i = 0; i < temp_uvs.size(); i++)
		cout << temp_uvs[i] << ", ";
	cout << endl;

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	std::vector<GLfloat> points;

	for (int i = 0; i < vertices.size(); i++)
	{
		points.push_back(temp_vertices[vertices[i] * 3]);
		points.push_back(temp_vertices[vertices[i] * 3 + 1]);
		points.push_back(temp_vertices[vertices[i] * 3 + 2]);

		points.push_back(temp_uvs[uvs[i] * 2]);
		points.push_back(temp_uvs[uvs[i] * 2 + 1]);

		points.push_back(temp_normals[normals[i] * 3]);
		points.push_back(temp_normals[normals[i] * 3 + 1]);
		points.push_back(temp_normals[normals[i] * 3 + 2]);
	}

	std::vector<unsigned short> arr;
	for (unsigned short i = 0; i < 36; i++)
		arr.push_back(i);

	GLuint buffer, buffer2;
	glGenBuffers(1, &buffer2);
	glBindBuffer(GL_ARRAY_BUFFER, buffer2);
	glBufferData(GL_ARRAY_BUFFER, points.size() * sizeof(GLfloat), &points[0], GL_STATIC_DRAW);
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, arr.size() * sizeof(unsigned short), &arr[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GL_FLOAT) * 8, 0);
	glEnableVertexAttribArray(0);


	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(GL_FLOAT) * 8, (void*)(sizeof(GL_FLOAT) * 3));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(GL_FLOAT) * 8, (void*)(sizeof(GL_FLOAT) * 5));
	glEnableVertexAttribArray(2);
	return true;
}

bool Object3d::loadTex(const char *file)
{
	GLuint textureID = SOIL_load_OGL_texture(
		file, SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glVertexAttribPointer(
		2,
		2,
		GL_FLOAT,
		GL_FALSE,
		sizeof(GL_FLOAT) * 8,
		(void*)(sizeof(GL_FLOAT) * 3));
	glEnableVertexAttribArray(2);

	glVertexAttribPointer(
		3,
		3,
		GL_FLOAT,
		GL_FALSE,
		sizeof(GL_FLOAT) * 8,
		(void*)(sizeof(GL_FLOAT) * 5));
	glEnableVertexAttribArray(3);

	return true;
}

void Object3d::Draw(GLuint program, GLint wm, GLint pos, GLint scale1)
{
	//sets up the world matrix for the drawing
	mat4 t = glm::translate(position);
	mat4 s = glm::scale(scale);

	mat4 m = t * s * rotation;
	glUniformMatrix4fv(wm, 1, GL_FALSE, &m[0][0]);

	glUniform3f(scale1, 1, 1, 1);

	glBindVertexArray(vao);
	glDrawElements(GL_TRIANGLES, vertices.size(), GL_UNSIGNED_SHORT, (void*)0);
}

void Object3d::Rotate(float angle, float x, float y, float z)
{
	rotation = glm::rotate(angle, vec3(x, y, z));
}


Object3d::~Object3d()
{
	glDeleteVertexArrays(vertices.size(), &vao);
}
