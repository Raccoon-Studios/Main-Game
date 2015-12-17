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
#include "GameState.h"
#include <array>

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

int oneScore = 0;
int twoScore = 0;
int oneRound = 0;
int twoRound = 0; 

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

Shape* onePoints [10];
Shape* twoPoints[10];

Shape* oneWins[3];
Shape* twoWins[3];

GameState state;

void init()
{
	state = play;
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
		//cout << "error ocurred" << endl;
	}

	helper.setShaderColor(shader, "uniformVector", 0.5f, 0.0f, 0.5f);
	mHelper.loadTextFile("Meshes//mesh2.obj", vertices, uvs, normals, vertexIndices, uvIndices, normalIndices);
	camera = Camera();
	cube = new Shape(vertices, vertices.size(), vertices.size() * 3, vertexIndices, uvIndices, normalIndices, uvs, normals, shader);
	cube->GetOBB()->SetIsBall(true);
	//cube2 = new Shape(vertices, vertices.size(), vertices.size() * 3, vertexIndices, uvIndices, normalIndices, uvs, normals, shader);
	
	for (int i = 0; i < 10;i++)
	{
		onePoints[i] = new Shape(vertices, vertices.size(), vertices.size() * 3, vertexIndices, uvIndices, normalIndices, uvs, normals, shader);

		twoPoints[i] = new Shape(vertices, vertices.size(), vertices.size() * 3, vertexIndices, uvIndices, normalIndices, uvs, normals, shader);
	}

	for (int i = 0; i < 3; i++)
	{
		oneWins[i] = new Shape(vertices, vertices.size(), vertices.size() * 3, vertexIndices, uvIndices, normalIndices, uvs, normals, shader);

		twoWins[i] = new Shape(vertices, vertices.size(), vertices.size() * 3, vertexIndices, uvIndices, normalIndices, uvs, normals, shader);
	}

	bWall = new Shape(vertices, vertices.size(), vertices.size() * 3, vertexIndices, uvIndices, normalIndices, uvs, normals, shader);
	tWall = new Shape(vertices, vertices.size(), vertices.size() * 3, vertexIndices, uvIndices, normalIndices, uvs, normals, shader);
	bWall->GetOBB()->SetIsWall(true);
	tWall->GetOBB()->SetIsWall(true);

	lpaddle1 = new Shape(vertices, vertices.size(), vertices.size() * 3, vertexIndices, uvIndices, normalIndices, uvs, normals, shader);
	lpaddle2 = new Shape(vertices, vertices.size(), vertices.size() * 3, vertexIndices, uvIndices, normalIndices, uvs, normals, shader);
	lpaddle3 = new Shape(vertices, vertices.size(), vertices.size() * 3, vertexIndices, uvIndices, normalIndices, uvs, normals, shader);
	lpaddle4 = new Shape(vertices, vertices.size(), vertices.size() * 3, vertexIndices, uvIndices, normalIndices, uvs, normals, shader);

	lpaddle1->GetOBB()->SetIsLeftPaddle(true);
	lpaddle2->GetOBB()->SetIsLeftPaddle(true);
	lpaddle3->GetOBB()->SetIsLeftPaddle(true);
	lpaddle4->GetOBB()->SetIsLeftPaddle(true);

	rpaddle1 = new Shape(vertices, vertices.size(), vertices.size() * 3, vertexIndices, uvIndices, normalIndices, uvs, normals, shader);
	rpaddle2 = new Shape(vertices, vertices.size(), vertices.size() * 3, vertexIndices, uvIndices, normalIndices, uvs, normals, shader);
	rpaddle3 = new Shape(vertices, vertices.size(), vertices.size() * 3, vertexIndices, uvIndices, normalIndices, uvs, normals, shader);
	rpaddle4 = new Shape(vertices, vertices.size(), vertices.size() * 3, vertexIndices, uvIndices, normalIndices, uvs, normals, shader);

	rpaddle1->GetOBB()->SetIsRightPaddle(true);
	rpaddle2->GetOBB()->SetIsRightPaddle(true);
	rpaddle3->GetOBB()->SetIsRightPaddle(true);
	rpaddle4->GetOBB()->SetIsRightPaddle(true);

	colliders.push_back(cube->GetOBB());
	//colliders.push_back(cube2->GetOBB());
	
	

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

	colliders.push_back(bWall->GetOBB());
	colliders.push_back(tWall->GetOBB());

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

	for (int i = 0; i < 10; i++)
	{
		onePoints[i]->SetPos(glm::vec3(0, -4.5, 5.17 - (i*.5)));
		twoPoints[i]->SetPos(glm::vec3(0, -4.5, -5.17 + (i*.5)));
	}
	for (int i = 0; i < 3; i++)
	{
		oneWins[i]->SetPos(glm::vec3(0, 4.5, 5.17 - (i*1.5)));
		twoWins[i]->SetPos(glm::vec3(0, 4.5, -5.17 + (i*1.5)));
	}


	GLfloat verticesTriangle[3 * 5] =
	{
		-1.0f, 0.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 
		0.0f, 1.0f, 1.0f, 1.0f, 1.0
	};


	glClearColor(0.0f, 0.0f, 0.5f, 1.0f);

	cube->SetVel(vec3(0, 0, .05));

	glfwSetTime(0.0);
	state = play;
}

void update()
{
		currentTime = float(glfwGetTime());
		deltaTime = currentTime - lastTime;
		deltaTime *= 75;
		//curRotAmount += rotAmountChange;
		//int state = glfwGetMouseButton(windowPtr, GLFW_MOUSE_BUTTON_LEFT);
		int stateW = glfwGetKey(windowPtr, GLFW_KEY_W);
		int stateA = glfwGetKey(windowPtr, GLFW_KEY_A);
		int stateS = glfwGetKey(windowPtr, GLFW_KEY_S);
		int stateD = glfwGetKey(windowPtr, GLFW_KEY_D);
		int stateUp = glfwGetKey(windowPtr, GLFW_KEY_UP);
		int stateDown = glfwGetKey(windowPtr, GLFW_KEY_DOWN);
		int stateLeft = glfwGetKey(windowPtr, GLFW_KEY_LEFT);
		int stateRight = glfwGetKey(windowPtr, GLFW_KEY_RIGHT);
		int stateQ = glfwGetKey(windowPtr, GLFW_KEY_Q);
		int stateEnter = glfwGetKey(windowPtr, GLFW_KEY_ENTER);

		if (stateW == GLFW_PRESS && !lPaddle[3]->GetOBB()->CollCheck(tWall->GetOBB()))
		{
			for (int i = 0; i < lPaddle.size(); i++)
			{
				lPaddle[i]->SetAccel(glm::vec3(0, -0.00125*deltaTime, 0));
			}

		}
		if (stateS == GLFW_PRESS && !lPaddle[0]->GetOBB()->CollCheck(bWall->GetOBB()))
		{
			for (int i = 0; i < lPaddle.size(); i++)
			{
				lPaddle[i]->SetAccel(glm::vec3(0, 0.00125*deltaTime, 0));
			}
		}

		if (stateUp == GLFW_PRESS && !rPaddle[3]->GetOBB()->CollCheck(tWall->GetOBB()))
		{
			for (int i = 0; i < rPaddle.size(); i++)
			{
				rPaddle[i]->SetAccel(glm::vec3(0, -0.00125*deltaTime, 0));
			}

		}
		if (stateDown == GLFW_PRESS && !rPaddle[0]->GetOBB()->CollCheck(bWall->GetOBB()))
		{
			for (int i = 0; i < rPaddle.size(); i++)
			{
				rPaddle[i]->SetAccel(glm::vec3(0, 0.00125*deltaTime, 0));
			}
		}


		if (stateA == GLFW_PRESS)
		{

			//camera.pos -= 0.005f * camera.getRight();
			cube->SetAccel(glm::vec3(0, 0, 0.00125*deltaTime));
		}

		if (stateD == GLFW_PRESS)
		{
			//camera.pos += 0.005f * camera.getRight();
			cube->SetAccel(glm::vec3(0, 0, -0.00125*deltaTime));

		}

		if (stateLeft == GLFW_PRESS)
		{

			//camera.pos -= 0.005f * camera.getRight();
			cube->SetAccel(glm::vec3(0, 0, 0.00125*deltaTime));
		}

		if (stateRight == GLFW_PRESS)
		{
			//camera.pos += 0.005f * camera.getRight();
			cube->SetAccel(glm::vec3(0, 0, -0.00125*deltaTime));

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

		//deltaTime /= 1000;
		lastTime = currentTime;
		if (state == oneWin)
		{

			if (stateEnter == GLFW_PRESS)
			{
				state = play;
			}
		}
		else if (state == twoWin)
		{

			if (stateEnter == GLFW_PRESS)
			{
				state = play;
			}
		}
		else
		{
			cube->Update();
			//cube2->Update();

			lpaddle1->Update();
			lpaddle2->Update();
			lpaddle3->Update();
			lpaddle4->Update();

			rpaddle1->Update();
			rpaddle2->Update();
			rpaddle3->Update();
			rpaddle4->Update();
		}

		//rWall->Update();
		//bWall->Update();

		for (int i = 0; i < colliders.size(); i++)
		{
			for (int k = 0; k < colliders.size(); k++)
			{
				if (colliders[i]->CollCheck(colliders[k]))
				{
					collCount++;
					//cout << "Collision # " << collCount <<  endl;
					//Call getCollding with, check the number 
					int collidingType = colliders[i]->GetCollidingWith(colliders[k]);

					//If it's colliding with a wall
					if (collidingType == 0){
						//cout << "yo its colliding with a wall!!" << endl;

						//If the original object is a ball
						if (colliders[i]->GetIsBall()){
							//	reverse ball velocity
							float zVel = colliders[i]->GetShape()->GetVel().z;
							float yVel = -1 * colliders[i]->GetShape()->GetVel().y;
							colliders[i]->GetShape()->SetVel(vec3(0, yVel, zVel));
						}
						//If the original object is the right paddle
						else if (colliders[i]->GetIsRightPaddle()){


							for (int m = 0; m < rPaddle.size(); m++){

								//Bounce off wall
								float yVel = -.5 * rPaddle[m]->GetVel().y;
								rPaddle[m]->SetVel(vec3(0, yVel, 0));
							}
						}
						//If the original object is the left paddle 
						else if (colliders[i]->GetIsLeftPaddle()){
							for (int m = 0; m < lPaddle.size(); m++){

								//Bounce off wall
								float yVel = -.5 * lPaddle[m]->GetVel().y;
								lPaddle[m]->SetVel(vec3(0, yVel, 0));
							}
						}
					}
					//If it's colliding with a ball
					else if (collidingType == 1){
						//cout << "yo its colliding with a ball!!" << endl;

						//If the original object is a paddle
						if (colliders[i]->GetIsRightPaddle() || colliders[i]->GetIsLeftPaddle()){

							//If it's the right paddle and the ball is not to the left (The ball is underneath)
							if ((colliders[i]->GetIsLeftPaddle()) && colliders[k]->GetCenter().z - 0.125f <= colliders[i]->GetCenter().z){
								colliders[i]->GetShape()->SetVel(vec3(colliders[i]->GetShape()->GetVel().x, 0, 0));
								for (int j = 0; j < 4; j++)
								{
									lPaddle[j]->SetVel(vec3(colliders[i]->GetShape()->GetVel().x, 0, 0));
								}
							}
							else if ((colliders[i]->GetIsLeftPaddle()) && colliders[k]->GetCenter().z - 0.125f >= colliders[i]->GetCenter().z){
								colliders[i]->GetShape()->SetVel(vec3(colliders[i]->GetShape()->GetVel().x, 0, 0));
								for (int j = 0; j < 4; j++)
								{
									lPaddle[j]->SetVel(vec3(colliders[i]->GetShape()->GetVel().x, 0, 0));
								}
							}
							if ((colliders[i]->GetIsRightPaddle()) && colliders[k]->GetCenter().z + 0.125f <= colliders[i]->GetCenter().z){
								colliders[i]->GetShape()->SetVel(vec3(colliders[i]->GetShape()->GetVel().x, 0, 0));
								for (int j = 0; j < 4; j++)
								{
									rPaddle[j]->SetVel(vec3(colliders[i]->GetShape()->GetVel().x, 0, 0));
								}
							}
							else if ((colliders[i]->GetIsRightPaddle()) && colliders[k]->GetCenter().z + 0.125f >= colliders[i]->GetCenter().z){
								colliders[i]->GetShape()->SetVel(vec3(colliders[i]->GetShape()->GetVel().x, 0, 0));
								for (int j = 0; j < 4; j++)
								{
									rPaddle[j]->SetVel(vec3(colliders[i]->GetShape()->GetVel().x, 0, 0));
								}
							}
						}
					}
					//If it's colliding with a paddle
					else if (collidingType == 2 || collidingType == 3){
						//cout << "yo its colliding with a paddle!!" << endl;

						//If the original object is a ball
						if (colliders[i]->GetIsBall()){
							//	reverse ball velocity
							float zVel = -1 * colliders[i]->GetShape()->GetVel().z;
							float yVel = colliders[k]->GetShape()->GetVel().y / 2;
							colliders[i]->GetShape()->SetVel(vec3(0, yVel, zVel));
						}

					}
					else{
						//cout << "stuff broke" << endl;
					}
					//Put in colliders[k]
				}
			}
		}

		if (cube->GetPos().z >= 5.3)
		{
			state = twoPoint;
		}
		else if (cube->GetPos().z <= -5.3)
		{
			state = onePoint;
		}

		//After a player scores, stuff resets to new positions with the ball drifting towards the player who didn't score
		if (state == onePoint)
		{
			cube->SetPos(vec3(0, 0, 0));

			lpaddle1->SetPos(glm::vec3(0, 0.5, 5.17));
			lpaddle2->SetPos(glm::vec3(0, 0.25, 5.17));
			lpaddle3->SetPos(glm::vec3(0, 0, 5.17));
			lpaddle4->SetPos(glm::vec3(0, -0.25, 5.17));

			rpaddle1->SetPos(glm::vec3(0, 0.5, -5.17));
			rpaddle2->SetPos(glm::vec3(0, 0.25, -5.17));
			rpaddle3->SetPos(glm::vec3(0, 0, -5.17));
			rpaddle4->SetPos(glm::vec3(0, -0.25, -5.17));

			cube->SetVel(vec3(0, 0, -.05));
			oneScore++;
			if ((oneScore >= 5 && twoScore <= oneScore - 2) || oneScore>=10)
			{
				state = oneWin;
				oneRound++;
				oneScore = 0;
				twoScore = 0;
			}
			else
			{
				state = play;
			}
		}
		else if (state == twoPoint)
		{
			cube->SetPos(vec3(0, 0, 0));

			lpaddle1->SetPos(glm::vec3(0, 0.5, 5.17));
			lpaddle2->SetPos(glm::vec3(0, 0.25, 5.17));
			lpaddle3->SetPos(glm::vec3(0, 0, 5.17));
			lpaddle4->SetPos(glm::vec3(0, -0.25, 5.17));

			rpaddle1->SetPos(glm::vec3(0, 0.5, -5.17));
			rpaddle2->SetPos(glm::vec3(0, 0.25, -5.17));
			rpaddle3->SetPos(glm::vec3(0, 0, -5.17));
			rpaddle4->SetPos(glm::vec3(0, -0.25, -5.17));

			cube->SetVel(vec3(0, 0, .05));

			twoScore++;
			if ((twoScore >= 5 && oneScore <= twoScore - 2) || twoScore >= 10)
			{
				state = twoWin;
				twoRound++;
				twoScore = 0;
				oneScore = 0;
			}
			else
			{
				state = play;
			}
		}

		if (oneRound >= 3 || twoRound >= 3)
		{
			state = oneWin;
			cube->SetPos(vec3(0, 0, 0));

			lpaddle1->SetPos(glm::vec3(0, 0.5, 5.17));
			lpaddle2->SetPos(glm::vec3(0, 0.25, 5.17));
			lpaddle3->SetPos(glm::vec3(0, 0, 5.17));
			lpaddle4->SetPos(glm::vec3(0, -0.25, 5.17));

			rpaddle1->SetPos(glm::vec3(0, 0.5, -5.17));
			rpaddle2->SetPos(glm::vec3(0, 0.25, -5.17));
			rpaddle3->SetPos(glm::vec3(0, 0, -5.17));
			rpaddle4->SetPos(glm::vec3(0, -0.25, -5.17));

			oneScore = 0;
			twoScore = 0;
			oneRound = 0;
			twoRound = 0;
		}
}

void draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glBindBuffer(shader, buffer);

	helper.setShaderColor(shader, "uniformVector", 0.7f, 0.6f, 0.3f);
	

	cube->Draw(cube->GetPos(), cube->GetScale(), cube->GetRotAxis(), cube->GetRotAmnt(), &cameraMat, &view);
	//cube2->Draw(cube2->GetPos(), cube2->GetScale(), cube2->GetRotAxis(), cube->GetRotAmnt(), &cameraMat, &view);
	
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

	for (int i = 0; i < oneScore; i++)
	{
		onePoints[i]->Draw(onePoints[i]->GetPos(), onePoints[i]->GetScale(), onePoints[i]->GetRotAxis(), onePoints[i]->GetRotAmnt(), &cameraMat, &view);
	}
	for (int i = 0; i < twoScore; i++)
	{
		twoPoints[i]->Draw(twoPoints[i]->GetPos(), twoPoints[i]->GetScale(), twoPoints[i]->GetRotAxis(), twoPoints[i]->GetRotAmnt(), &cameraMat, &view);
	}
	for (int i = 0; i < oneRound; i++)
	{
		oneWins[i]->Draw(oneWins[i]->GetPos(), oneWins[i]->GetScale(), oneWins[i]->GetRotAxis(), oneWins[i]->GetRotAmnt(), &cameraMat, &view);
	}
	for (int i = 0; i < twoRound; i++)
	{
		twoWins[i]->Draw(twoWins[i]->GetPos(), twoWins[i]->GetScale(), twoWins[i]->GetRotAxis(), twoWins[i]->GetRotAmnt(), &cameraMat, &view);
	}

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
	//cout << "bWall Pos: " << pos.x << " " << pos.y << " " << pos.z << endl;
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
	//glfwSetInputMode(windowPtr, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

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