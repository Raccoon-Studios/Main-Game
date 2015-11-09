#pragma once
#include<glew.h>
#include<glfw3.h>
#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>
#include"ShaderHelpers.h"
#include"GameObject.h"
#include <vector>
using namespace glm;
using namespace std;

class GameWorld
{
public:
	GameWorld(GLuint programIndex);
	~GameWorld();
	static bool mouseButtonHeld;
	static void update();
	static void draw();
	static void mouseMove(GLFWwindow* windowPtr, double x, double y);
	static vec2 getCursorPos(GLFWwindow* windowPtr);
	static void mouseClick(GLFWwindow* windowPtr, int button, int action, int mods);
private:
	static float activeTime;
	static GLuint programIndex;
	static vector<GameObject> triangles;
	//static GLuint getProgram;
};

