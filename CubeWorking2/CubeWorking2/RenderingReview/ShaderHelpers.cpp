#include "ShaderHelpers.h"
#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>
using namespace glm;

char* loadTextFile(const char* file){

	ifstream inFile(file, ios::binary);

	if (inFile.is_open()){
		inFile.seekg(0, ios::end);
		int length = (int)inFile.tellg();

		inFile.seekg(0, ios::beg);

		char* fileContents = new char[length + 1];

		inFile.read(fileContents, length);
		fileContents[length] = 0;

		/*for(int i = 0; i<length;i++){
		cout<<fileContents[i];
		}*/
		inFile.close();

		return fileContents;
	}
	return 0;
}

GLuint loadShader(const char* file, GLenum shaderType){
	const char* fileContents = loadTextFile(file);

	if (!fileContents){
		cout << "There was an error loading the shader." << endl;
		return 0;
	}
	else{
		GLuint shaderIndex = glCreateShader(shaderType);
		glShaderSource(shaderIndex, 1, &fileContents, 0);
		glCompileShader(shaderIndex);
		delete fileContents;

		GLint compile;
		glGetShaderiv(shaderIndex, GL_COMPILE_STATUS, &compile);
		if (compile){
			return shaderIndex;
		}
		else{
			GLint logLength;
			glGetShaderiv(shaderIndex, GL_INFO_LOG_LENGTH, &logLength);

			char* logArray = new char[logLength];
			glGetShaderInfoLog(shaderIndex, logLength, 0, logArray);

			for (int i = 0; i<logLength; i++){
				cout << logArray[i];
			}
			cout << "\n";

			glDeleteShader(shaderIndex);
			delete logArray;

			return 0;
		}
	}

}

GLuint loadShaderProgram(const char* vertexFile, const char* fragmentFile){
	GLuint vertexIndex = loadShader(vertexFile, GL_VERTEX_SHADER);
	if (vertexIndex == 0){
		return 0;
	}

	GLuint fragmentIndex = loadShader(fragmentFile, GL_FRAGMENT_SHADER);
	if (fragmentIndex == 0){
		return 0;
	}

	GLuint programIndex = glCreateProgram();
	glAttachShader(programIndex, vertexIndex);
	glAttachShader(programIndex, fragmentIndex);
	glLinkProgram(programIndex);

	GLint linked;
	glGetProgramiv(programIndex, GL_LINK_STATUS, &linked);

	if (linked == 0){
		GLint logLength;
		glGetProgramiv(programIndex, GL_INFO_LOG_LENGTH, &logLength);

		char* logArray = new char[logLength];
		glGetProgramInfoLog(programIndex, logLength, 0, logArray);

		glDeleteProgram(programIndex);

		for (int i = 0; i<logLength; i++){
			cout << logArray[i];
		}
		cout << "\n";


		delete logArray;

		return 0;
	}
	else{
		return programIndex;
	}
}

void setShaderColor(GLuint programIndex, const char* name, float redVal, float greenVal, float blueVal){
	GLint uniformLocation = glGetUniformLocation(programIndex, name);
	glProgramUniform4f(programIndex, uniformLocation, redVal, greenVal, blueVal, 1.0f);

}

void setShaderVec2(GLuint programIndex, const char* name, vec2 vecToSend){
	GLint uniformLocation = glGetUniformLocation(programIndex, name);
	glProgramUniform2fv(programIndex, uniformLocation, 1, &vecToSend[0]);
}

void setShaderMatrix(GLuint programIndex, const char* name, const mat4 &matToSend){
	GLint uniformLocation = glGetUniformLocation(programIndex, name);
	glProgramUniformMatrix4fv(programIndex, uniformLocation, 1, GL_FALSE, &matToSend[0][0]);
}
void setShaderMat4x4(GLuint programIndex, const char* name, const mat4x4 &matToSend){
	GLint uniformLocation = glGetUniformLocation(programIndex, name);
	glProgramUniformMatrix4fv(programIndex, uniformLocation, 1, GL_FALSE, &matToSend[0][0]);
}