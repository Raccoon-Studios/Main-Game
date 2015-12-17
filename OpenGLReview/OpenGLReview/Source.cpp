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
int debugLoop = 0;
int collCount = 0;
GLFWwindow* windowPtr;
mat4 view;

vector<Obb*> colliders;
vector<Shape*> lPaddle;
vector<Shape*> rPaddle;

Shape* cube;
Shape* cube2;


Shape* bWall;
Shape* tWall;

Shape* lpaddle1;
Shape* lpaddle2;
Shape* lpaddle3;
Shape* lpaddle4;

Shape* rpaddle1;
Shape* rpaddle2;
Shape* rpaddle3;
Shape* rpaddle4;

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
	
	bWall = new Shape(vertices, vertices.size(), vertices.size() * 3, vertexIndices, uvIndices, normalIndices, uvs, normals, shader);
	tWall = new Shape(vertices, vertices.size(), vertices.size() * 3, vertexIndices, uvIndices, normalIndices, uvs, normals, shader);

	lpaddle1 = new Shape(vertices, vertices.size(), vertices.size() * 3, vertexIndices, uvIndices, normalIndices, uvs, normals, shader);
	lpaddle2 = new Shape(vertices, vertices.size(), vertices.size() * 3, vertexIndices, uvIndices, normalIndices, uvs, normals, shader);
	lpaddle3 = new Shape(vertices, vertices.size(), vertices.size() * 3, vertexIndices, uvIndices, normalIndices, uvs, normals, shader);
	lpaddle4 = new Shape(vertices, vertices.size(), vertices.size() * 3, vertexIndices, uvIndices, normalIndices, uvs, normals, shader);

	rpaddle1 = new Shape(vertices, vertices.size(), vertices.size() * 3, vertexIndices, uvIndices, normalIndices, uvs, normals, shader);
	rpaddle2 = new Shape(vertices, vertices.size(), vertices.size() * 3, vertexIndices, uvIndices, normalIndices, uvs, normals, shader);
	rpaddle3 = new Shape(vertices, vertices.size(), vertices.size() * 3, vertexIndices, uvIndices, normalIndices, uvs, normals, shader);
	rpaddle4 = new Shape(vertices, vertices.size(), vertices.size() * 3, vertexIndices, uvIndices, normalIndices, uvs, normals, shader);

	colliders.push_back(cube->GetOBB());
	colliders.push_back(cube2->GetOBB());
	
	colliders.push_back(bWall->GetOBB());
	colliders.push_back(tWall->GetOBB());

	colliders.push_back(lpaddle1->GetOBB());
	colliders.push_back(lpaddle2->GetOBB());
	colliders.push_back(lpaddle3->GetOBB());
	colliders.push_back(lpaddle4->GetOBB());

	colliders.push_back(rpaddle1->GetOBB());
	colliders.push_back(rpaddle2->GetOBB());
	colliders.push_back(rpaddle3->GetOBB());
	colliders.push_back(rpaddle4->GetOBB());

	lPaddle.push_back(lpaddle1);
	lPaddle.push_back(lpaddle2);
	lPaddle.push_back(lpaddle3);
	lPaddle.push_back(lpaddle4);

	rPaddle.push_back(rpaddle1);
	rPaddle.push_back(rpaddle2);
	rPaddle.push_back(rpaddle3);
	rPaddle.push_back(rpaddle4);

	lpaddle1->SetScale(glm::vec3(0.25, 0.25, 0.25));
	lpaddle1->SetPos(glm::vec3(0, 0.5, 5.17));

	lpaddle2->SetScale(glm::vec3(0.25, 0.25, 0.25));
	lpaddle2->SetPos(glm::vec3(0, 0.25, 5.17));

	lpaddle3->SetScale(glm::vec3(0.25, 0.25, 0.25));
	lpaddle3->SetPos(glm::vec3(0, 0, 5.17));

	lpaddle4->SetScale(glm::vec3(0.25, 0.25, 0.25));
	lpaddle4->SetPos(glm::vec3(0, -0.25, 5.17));

	rpaddle1->SetScale(glm::vec3(0.25, 0.25, 0.25));
	rpaddle1->SetPos(glm::vec3(0, 0.5, -5.17));

	rpaddle2->SetScale(glm::vec3(0.25, 0.25, 0.25));
	rpaddle2->SetPos(glm::vec3(0, 0.25, -5.17));

	rpaddle3->SetScale(glm::vec3(0.25, 0.25, 0.25));
	rpaddle3->SetPos(glm::vec3(0, 0, -5.17));

	rpaddle4->SetScale(glm::vec3(0.25, 0.25, 0.25));
	rpaddle4->SetPos(glm::vec3(0, -0.25, -5.17));


	bWall->SetScale(glm::vec3(0.25, 0.25, 10.5));
	bWall->SetPos(glm::vec3(0, 3.67, 0));

	tWall->SetScale(glm::vec3(0.25, 0.25, 10.5));
	tWall->SetPos(glm::vec3(0, -3.67, 0));



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
		for (int i = 0; i < lPaddle.size(); i++)
		{
			lPaddle[i]->SetAccel(glm::vec3(0, -0.00125, 0));
		}
		
	}

	if (stateA == GLFW_PRESS)
	{
		
		//camera.pos -= 0.005f * camera.getRight();
		cube->SetAccel(glm::vec3(0,0, 0.00125));
	}

	if (stateS == GLFW_PRESS)
	{
		for (int i = 0; i < lPaddle.size(); i++)
		{
			lPaddle[i]->SetAccel(glm::vec3(0, 0.00125, 0));
		}
	}

	if (stateD == GLFW_PRESS)
	{
		//camera.pos += 0.005f * camera.getRight();
		cube->SetAccel(glm::vec3(0, 0, -0.00125));

	}

	if (stateQ == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(windowPtr, 1);

	}

	/*
	double cursorXPos;
	double cursorYPos;
	double convXPos;
	double convYPos;
	glfwGetCursorPos(windowPtr, &cursorXPos, &cursorYPos);
	convXPos = 2.0f * (((float)cursorXPos / (float)windowWidth) - 0.5f);
	convYPos = -2.0f * (((float)cursorYPos / (float)windowHeight) - 0.5f);
	*/

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

	//deltaTime /= 1000;
	lastTime = currentTime;
	
	cube->Update();
	cube2->Update();

	lpaddle1 ->Update();
	lpaddle2->Update();
	lpaddle3->Update();
	lpaddle4->Update();

	rpaddle1->Update();
	rpaddle2->Update();
	rpaddle3->Update();
	rpaddle4->Update();

	//rWall->Update();
	//bWall->Update();

	for (int i = 0; i < colliders.size(); i++)
	{
		for (int k = i + 1; k < colliders.size(); k++)
		{
			if (colliders[i]->CollCheck(colliders[k]))
			{
				collCount++;
				cout << "Collision # " << collCount <<  endl;
			}
		}
	}
	
	
	
}

void draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glBindBuffer(shader, buffer);

	helper.setShaderColor(shader, "uniformVector", 0.7f, 0.6f, 0.3f);
	

	cube->Draw(cube->GetPos(), cube->GetScale(), cube->GetRotAxis(), cube->GetRotAmnt(), &cameraMat, &view);
	cube2->Draw(cube2->GetPos(), cube2->GetScale(), cube2->GetRotAxis(), cube->GetRotAmnt(), &cameraMat, &view);
	
	bWall->Draw(bWall->GetPos(), bWall->GetScale(), bWall->GetRotAxis(), bWall->GetRotAmnt(), &cameraMat, &view);
	tWall->Draw(tWall->GetPos(), tWall->GetScale(), tWall->GetRotAxis(), tWall->GetRotAmnt(), &cameraMat, &view);

	lpaddle1->Draw(lpaddle1->GetPos(), lpaddle1->GetScale(), lpaddle1->GetRotAxis(), lpaddle1->GetRotAmnt(), &cameraMat, &view);
	lpaddle2->Draw(lpaddle2->GetPos(), lpaddle2->GetScale(), lpaddle2->GetRotAxis(), lpaddle2->GetRotAmnt(), &cameraMat, &view);
	lpaddle3->Draw(lpaddle3->GetPos(), lpaddle3->GetScale(), lpaddle3->GetRotAxis(), lpaddle3->GetRotAmnt(), &cameraMat, &view);
	lpaddle4->Draw(lpaddle4->GetPos(), lpaddle4->GetScale(), lpaddle4->GetRotAxis(), lpaddle4->GetRotAmnt(), &cameraMat, &view);

	rpaddle1->Draw(rpaddle1->GetPos(), rpaddle1->GetScale(), rpaddle1->GetRotAxis(), rpaddle1->GetRotAmnt(), &cameraMat, &view);
	rpaddle2->Draw(rpaddle2->GetPos(), rpaddle2->GetScale(), rpaddle2->GetRotAxis(), rpaddle2->GetRotAmnt(), &cameraMat, &view);
	rpaddle3->Draw(rpaddle3->GetPos(), rpaddle3->GetScale(), rpaddle3->GetRotAxis(), rpaddle3->GetRotAmnt(), &cameraMat, &view);
	rpaddle4->Draw(rpaddle4->GetPos(), rpaddle4->GetScale(), rpaddle4->GetRotAxis(), rpaddle4->GetRotAmnt(), &cameraMat, &view);

	glFlush();

}

void mouseCallback(GLFWwindow*, double xPos, double yPos)
{
	/*
	GLfloat lastX = 400;
	GLfloat lastY = 400;

	GLfloat xOffset = xPos - lastX;
	GLfloat yOffset = yPos - lastY;

	GLfloat sensitivity = 0.05f;
	xOffset *= sensitivity;
	yOffset *= sensitivity;

	camera.turn(xOffset, yOffset);
	glfwSetCursorPos(windowPtr, 400, 400);
	*/
}

void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
	glm::vec3 pos = bWall->GetPos();
	cout << "bWall Pos: " << pos.x << " " << pos.y << " " << pos.z << endl;
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