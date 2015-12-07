#pragma once
#include <glew.h>

using namespace std;
class ShaderHelper
{
public:
	ShaderHelper(void);
	~ShaderHelper(void);

	//loads text file containing shader
	char* loadTextFile(const char* file);

	//loads shaders, calls load text file
	GLuint loadShader(const char* vertexFile, GLenum shaderType);

	//loads shader programs, calls loadShader
	GLuint loadShaderProgram(const char* vertexFile, const char* fragmentFile);
	void setShaderColor(GLuint shaderProgramIndex, const char* uniformVarName, float red, float green, float blue);
	//void setShaderVec2(GLuint shaderProgramIndex, const char* varName, glm::vec2 vecToSend);

};

