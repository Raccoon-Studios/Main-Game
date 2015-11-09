#include "GameWorld.h"


GameWorld::GameWorld(GLuint programIndex)
{
	this->programIndex = programIndex;

	this->activeTime = 0;

	float currentTime = float(glfwGetTime());
	float dt = currentTime - activeTime;
	activeTime = currentTime;

	mouseButtonHeld = false;
	triangles.reserve(20);

}


GameWorld::~GameWorld()
{
}

void GameWorld::update() {
	for (int i = 0; i < triangles.size(); i++){
		triangles[i].update(activeTime);
	}
}

void GameWorld::draw() {
	for (int i = 0; i < triangles.size(); i++){
		triangles[i].draw();
	}
}

void GameWorld::mouseMove(GLFWwindow* windowPtr, double x, double y) {
	vec2 cursorPos = getCursorPos(windowPtr);
}

vec2 GameWorld::getCursorPos(GLFWwindow* windowPtr) {
	double xpos, ypos;
	glfwGetCursorPos(windowPtr, &xpos, &ypos);
	int width, height;
	glfwGetWindowSize(windowPtr, &width, &height);
	vec2 cursorPos;
	cursorPos.x = 2.0f * (float(xpos) / float(width)) - 1.0f;
	cursorPos.y = (2.0f * (float(xpos) / float(width)) - 1.0f)*-1.0f;

	return cursorPos;
}


void GameWorld::mouseClick(GLFWwindow* windowPtr, int button, int action, int mods) {
	if (button == GLFW_MOUSE_BUTTON_LEFT	&& action == GLFW_PRESS){
		mouseButtonHeld = true;

		vec2 cursorPos = getCursorPos(windowPtr);

		triangles.push_back(GameObject(programIndex));
	}

}