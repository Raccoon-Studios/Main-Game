#include <glew.h>
#include <glfw3.h>
#include"ShaderHelper.h"
#include "Shape.h"
#include "Entity.h"
#include "MeshHelper.h"
#include <vector>
#include<iostream>
#include<fstream>
#include<time.h>
#include <glm\gtx\transform.hpp>
#include "Camera.h"
#include <SOIL.h>

#pragma once
using namespace std;

float curRotAmount = 0.0;
float rotAmountChange = 0.002;

vector<glm::vec3> vertices;
vector<glm::vec2> uvs;
vector<glm::vec3> normals;

vector<unsigned int > vertexIndices;
vector<unsigned int > uvIndices;
vector<unsigned int > normalIndices;

ShaderHelper helper;
MeshHelper mHelper;
GLuint buffer;
GLuint VertArrayObj;
GLuint shader;

Camera camera;
mat4 cameraMat;

GLfloat lastX = 400;
GLfloat lastY = 400;


float lastTime;
int windowWidth = 800;
int windowHeight = 800;
int clickTrack = 0;
float deltaTime;
float currentTime;
int triCount = 0;

GLFWwindow* windowPtr;
mat4 view;

Shape* cube;
Shape* cube2;
Entity cube1;


void init()
{
	srand(time(NULL));
	
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glEnable(GL_DEPTH_TEST);

	shader = helper.loadShaderProgram("Shaders//vertexShader.glsl", "Shaders//fragmentShader.glsl");
	if (shader != 0)
	{
		glUseProgram(shader);
	}
	else
	{
		cout << "error ocurred" << endl;
	}

	helper.setShaderColor(shader, "uniformVector", 0.5f, 0.0f, 0.5f);
	mHelper.loadTextFile("Meshes//mesh2.obj", vertices, uvs, normals, vertexIndices, uvIndices, normalIndices);
	camera = Camera();
	cube = new Shape(vertices, vertices.size(), vertices.size() * 3, vertexIndices, uvIndices, normalIndices, uvs, normals, shader);
	cube2 = new Shape(vertices, vertices.size(), vertices.size() * 3, vertexIndices, uvIndices, normalIndices, uvs, normals, shader);

	GLfloat verticesTriangle[3 * 5] =
	{
		-1.0f, 0.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 
		0.0f, 1.0f, 1.0f, 1.0f, 1.0
	};


	glClearColor(0.0f, 0.0f, 0.5f, 1.0f);
}

void update()
{
	//curRotAmount += rotAmountChange;
	//int state = glfwGetMouseButton(windowPtr, GLFW_MOUSE_BUTTON_LEFT);
	int stateW = glfwGetKey(windowPtr, GLFW_KEY_W);
	int stateA = glfwGetKey(windowPtr, GLFW_KEY_A);
	int stateS = glfwGetKey(windowPtr, GLFW_KEY_S);
	int stateD = glfwGetKey(windowPtr, GLFW_KEY_D);
	int stateQ = glfwGetKey(windowPtr, GLFW_KEY_Q);

	if (stateW == GLFW_PRESS)
	{
		camera.pos += 0.005f * camera.getForward();
		
	}

	if (stateA == GLFW_PRESS)
	{
		
		camera.pos -= 0.005f * camera.getRight();
	}

	if (stateS == GLFW_PRESS)
	{

		camera.pos -= 0.005f * camera.getForward();
	}

	if (stateD == GLFW_PRESS)
	{
		camera.pos += 0.005f * camera.getRight();

	}

	if (stateQ == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(windowPtr, 1);

	}

	double cursorXPos;
	double cursorYPos;
	double convXPos;
	double convYPos;
	glfwGetCursorPos(windowPtr, &cursorXPos, &cursorYPos);
	convXPos = 2.0f * (((float)cursorXPos / (float)windowWidth) - 0.5f);
	convYPos = -2.0f * (((float)cursorYPos / (float)windowHeight) - 0.5f);

	//camera.yaw += 0.001f;
	//camera.pitch += 0.001f;
	camera.getForward();
	camera.getRight();
	camera.getUp();
	view = lookAt(camera.pos, camera.getLookAt(), vec3(0.0f, 1.0f, 0.0f));
	mat4 projection = perspective(100.0f, 1.0f, 0.01f, 1000.0f);
	cameraMat = projection * view;


	currentTime = float(glfwGetTime());
	deltaTime = currentTime - lastTime;
	cube1.Update(deltaTime);
	//deltaTime /= 1000;
	lastTime = currentTime;
	
	
	
}

void draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glBindBuffer(shader, buffer);

	helper.setShaderColor(shader, "uniformVector", 0.7f, 0.6f, 0.3f);
	

	cube->Draw(glm::vec3(0, 0, 0), glm::vec3(0.25, 0.25, 0.25), glm::vec3(0, 0, 1), curRotAmount, &cameraMat, &view);
	cube2->Draw(glm::vec3(-0.5, -0.5, -0.5), glm::vec3(0.5, 0.25, 0.5), glm::vec3(0, 0, 1), curRotAmount, &cameraMat, &view);
	//cube1.Draw();
	
	
	//triangle->Draw(triangle->currentPosition, triangle->scale, triangle->rotationAxis, triangle->rotationAmount);
	
	/*
	for (int i = 0; i < 100; i++)
	{
		triVec[i].Draw();
	}
	tri1.Draw();
	*/
	//cout << "Current Time: " << currentTime << endl;
	//cout << "Last Time: " << lastTime << endl;
	//cout << deltaTime << endl;
	glFlush();

}

void mouseCallback(GLFWwindow*, double xPos, double yPos)
{
	GLfloat lastX = 400;
	GLfloat lastY = 400;

	GLfloat xOffset = xPos - lastX;
	GLfloat yOffset = yPos - lastY;

	GLfloat sensitivity = 0.05f;
	xOffset *= sensitivity;
	yOffset *= sensitivity;

	camera.turn(xOffset, yOffset);
	glfwSetCursorPos(windowPtr, 400, 400);

}

void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
	//int state = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);

	/*if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
	{
		camera.pos.z += 0.004;
	}*/

	//if (button == GLFW_MOUSE_BUTTON_LEFT && state == GLFW_PRESS)
	{/*
		double cursorXPos;
		double cursorYPos;
		double convXPos;
		double convYPos;
		glfwGetCursorPos(window, &cursorXPos, &cursorYPos);
		convXPos = 2.0f * (((float)cursorXPos / (float)windowWidth) - 0.5f);
		convYPos = -2.0f * (((float)cursorYPos / (float)windowHeight) - 0.5f);
		//cout << "CursorPos: " << cursorXPos << endl << cursorYPos << endl;
		//cout << "ConvPos: " << convXPos << endl << convYPos << endl;
		//triVec[triCount].setPosition(convXPos, convYPos);
		triCount++;
		if (triCount > 99)
		{
			triCount = 0;
		}
		//tri1.setPosition(convXPos, convYPos);
		//triangle->currentPosition.x = convXPos;
		//triangle->currentPosition.y = convYPos;

		*/
	}
}

int main()
{
	//initialize the library
	if (!glfwInit())
		return -1;

	//Create a windowed mode winow and its OpenGL context
	windowPtr = glfwCreateWindow(windowWidth, windowHeight, "Window", NULL, NULL);
	if (!windowPtr)
	{
		glfwTerminate();
		return -1;
	}

	//Make the window's context current
	glfwMakeContextCurrent(windowPtr);

	if (glewInit() != GLEW_OK) return false;
	glewExperimental = GLU_TRUE;

	init();

	glfwSetInputMode(windowPtr, GLFW_STICKY_MOUSE_BUTTONS, GL_TRUE);
	glfwSetInputMode(windowPtr, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	glfwSetCursorPosCallback(windowPtr, mouseCallback);
	glfwSetMouseButtonCallback(windowPtr, MouseButtonCallback);

	while (!glfwWindowShouldClose(windowPtr))
	{
		/*
		int windowWCoor;
		int windowHCoor;
		glfwGetWindowSize(windowPtr, &windowWCoor, &windowHCoor);
		*/
		
		update();
		draw();

		glfwSwapBuffers(windowPtr);

		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
	//call  init method here

	//glClearColor(0.5f, 0.392f, 0.123f, 1.0f);
	/*
	GLuint vShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vShader, 1, &vShaderCode, 0);
	glCompileShader(vShader);

	GLuint fShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fShader, 1, &fShaderCode, 0);
	glCompileShader(fShader);

	GLuint program = glCreateProgram();
	glAttachShader(program, vShader);
	glAttachShader(program, fShader);
	glLinkProgram(program);
	*/
}