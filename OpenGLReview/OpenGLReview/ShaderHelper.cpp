#include "ShaderHelper.h"
#include <glew.h>

#include <fstream>
#include <iostream>

using namespace std;



ShaderHelper::ShaderHelper(void)
{

}


ShaderHelper::~ShaderHelper(void)
{
}

char* ShaderHelper::loadTextFile(const char* file)
{
	ifstream inFile(file, ios::binary);
	if (inFile.is_open())
	{
		//seek & get length
		inFile.seekg(0, ios::end);
		int length = (int)inFile.tellg();

		//seek back to beginning
		inFile.seekg(0, ios::beg);

		//make array to hold file
		char* fileContents = new char[length + 1];

		//read file & set null ptr
		inFile.read(fileContents, length);
		fileContents[length] = 0;

		//done with file
		inFile.close();

		return fileContents;
	}
	else
	{
		return nullptr;
	}
}

GLuint ShaderHelper::loadShader(const char* file, GLenum shaderType)
{
	const char* fileContents = loadTextFile(file);
	cout << fileContents << endl;
	if (fileContents == nullptr)
	{
		cout << "error occurred, file not open." << endl;
		return 0;
	}
	else
	{
		GLuint shader = glCreateShader(shaderType);
		glShaderSource(shader, 1, &fileContents, 0);
		glCompileShader(shader);
		delete[]fileContents;
		GLint index;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &index);
		if (index == GL_TRUE)
		{
			return shader;
		}
		else
		{
			GLint logLength;
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLength);
			char* log = new char[logLength];

			glGetShaderInfoLog(shader, logLength, 0, log);
			cout << log << endl;
			glDeleteShader(shader);
			delete[] &log;
		}
	}
}

GLuint ShaderHelper::loadShaderProgram(const char* vertexFile, const char* fragmentFile)
{
	GLuint vertShader = loadShader(vertexFile, GL_VERTEX_SHADER);
	if (vertShader == 0)
	{
		return 0;
	}

	GLuint fragShader = loadShader(fragmentFile, GL_FRAGMENT_SHADER);
	if (fragShader == 0)
	{
		return 0;
	}

	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, fragShader);
	glAttachShader(shaderProgram, vertShader);
	glLinkProgram(shaderProgram);
	GLint linkStatus;
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &linkStatus);
	if (linkStatus == GL_TRUE)
	{
		return shaderProgram;
	}

	else
	{
		GLint logLength;
		glGetProgramiv(shaderProgram, GL_INFO_LOG_LENGTH, &logLength);

		char* log = new char[logLength];

		glGetProgramInfoLog(shaderProgram, logLength, 0, log);
		cout << log << endl;
		delete &shaderProgram;
		delete[] & log;
		return 0;
	}
}

void ShaderHelper::setShaderColor(GLuint shaderProgram, const char* uniformVarName, float red, float green, float blue)
{
	GLint uniformLoc;
	uniformLoc = glGetUniformLocation(shaderProgram, uniformVarName);
	if (uniformLoc != -1)
	{
		glProgramUniform4f(shaderProgram, uniformLoc, red, blue, green, 1.0f);
	}

	else
	{

	}
}
