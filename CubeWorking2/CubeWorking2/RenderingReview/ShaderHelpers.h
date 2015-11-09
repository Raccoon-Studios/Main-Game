#pragma once
#include<glew.h>
#include<glfw3.h>

#include <fstream>
#include <iostream>
#include <stdio.h>
#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>
using namespace glm;
using namespace std;

char* loadTextFile(const char* file);
GLuint loadShader(const char* file, GLenum shaderType);
GLuint loadShaderProgram(const char* vertexFile, const char* fragmentFile);
void setShaderColor(GLuint programIndex, const char* name, float redVal, float greenVal, float blueVal);
void setShaderVec2(GLuint programIndex, const char* name, vec2 vecToSend);
void setShaderMatrix(GLuint programIndex, const char* name, const mat4 &matToSend);