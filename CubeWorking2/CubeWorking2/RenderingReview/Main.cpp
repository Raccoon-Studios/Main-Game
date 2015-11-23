#include<glew.h>
#include<glfw3.h>
#include "ShaderHelpers.h"
#include "Object3d.h"
#include "Camera.h"
using namespace std;
#include<sstream>

GLuint bufferIndex;
GLuint arrayIndex;
GLint programIndex;

const GLsizei numVertices = 5;
const GLsizei numComponents = numVertices * 5;
GLint worldMatrix;
GLint currentPosition;
GLint currentScale;
float rotationAngle;
vec3 rotationAxis;

const GLsizei floatsPerVert = 36 * 5;

Camera camera;

vec3 cameraPos;
vec3 cameraUp;
vec3 cameraFront;
float lastTime = 0;
float lastCursorX = 400;
float lastCursorY = 400;
float yaw = 0;
float pitch = 0;

const GLsizei numCubeVertices = 36;
const GLsizei numCubeComponents = numCubeVertices * 6;

void init();
void update();
void draw();
vector<GLfloat> loadOBJ(const char* filename);
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
static void error_callback(int error, const char* description);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);

bool mouseDragging;
Object3d *player;


int main(void)
{

	GLFWwindow* window;
	mouseDragging = false;
	glfwSetErrorCallback(error_callback);

	if (!glfwInit())
		return -1;

	window = glfwCreateWindow(800, 800, "Game Engine Review", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);

	glewExperimental = GLU_TRUE;

	if (glewInit() != GLEW_OK) {
		return -1;
	}
	
	glfwSetKeyCallback(window, key_callback);
	glfwSetMouseButtonCallback(window, mouse_button_callback);
	glfwSetCursorPosCallback(window, cursor_position_callback);
	init();

	while (!glfwWindowShouldClose(window))
	{
		float ratio;
		int width, height;
		glfwGetFramebufferSize(window, &width, &height);
		ratio = width / (float)height;
		glViewport(0, 0, width, height);

		update();
		draw();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwDestroyWindow(window);
	glfwTerminate();
	return -1;
}

void init() {
	//cout<<"Initializing"<<endl;
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);



	//cameraPos = vec3(0.0f, 0.0f, 1.5f);
	//cameraUp = vec3(0.0f, 1.0f, 0.0f);
	//cameraFront = vec3(0.0f, 0.0f, -1.0f);

	camera = Camera();

	currentPosition = glGetUniformLocation(programIndex, "position");
	currentScale = glGetUniformLocation(programIndex, "scale"); 
	worldMatrix = glGetUniformLocation(programIndex, "worldMatrix");
	float rotationAngle = 0;
	vec3 rotationAxis = vec3(0, 0, 1);

	glGenVertexArrays(1, &arrayIndex);
	glBindVertexArray(arrayIndex);

	player = new Object3d("cube2.obj");

	player->loadObj();

	player->loadTex("archer.jpg");
	player->position = vec3(0, 0, 0);
	player->scale = vec3(1, 1, 1);

	glClearColor(0.392f, 0.584f, 0.929f, 1.0f);

	programIndex = loadShaderProgram("Shaders/vertexShader.glsl", "Shaders/fragmentShader.glsl");
	if (programIndex) {
		glUseProgram(programIndex);
	}

	setShaderColor(programIndex, "color", 1, 0, 1);
	//worldMatrix = translate(currentPosition) * scale(currentScale) * rotate(rotationAngle, rotationAxis);
	//setShaderMatrix(programIndex, "worldMatrix", worldMatrix);

}

void update() {
	//Camera Stuff
		camera.getForward();
		camera.getRight();
		camera.getUp();

		GLfloat radius = 1.0f;
		GLfloat camX = sin(glfwGetTime())* radius;
		GLfloat camZ = cos(glfwGetTime())* radius;

		mat4 viewMatrix = lookAt(camera.pos, camera.getLookAt(), vec3(0.0f, 1.0f, 0.0f));

		mat4 perspectiveMatrix = glm::perspective(100.0f, 1.0f, 0.01f, 1000.0f);
		perspectiveMatrix *= viewMatrix;
		setShaderMatrix(programIndex, "cameraMatrix", perspectiveMatrix);
		cout << cameraPos.x << "  " << cameraPos.y <<  endl;
	//end




	
}

void draw() {
	//cout<<"Drawing"<<endl;

	player->Draw(programIndex, worldMatrix, currentPosition, currentScale);
	glFlush();


}  

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods){
	//If mouse is clicking
	if (button == GLFW_MOUSE_BUTTON_LEFT	&& action == GLFW_PRESS){
		//Calculate World Position
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);
		int width, height;
		glfwGetWindowSize(window, &width, &height);

		double worldX, worldY;
		if (xpos > width / 2){
			worldX = (xpos - (width / 2)) / (width / 2);
		}
		else{
			worldX = (xpos / (width / 2)) - 1;
		}
		if (ypos > height / 2){
			worldY = (-1 * (ypos - height / 2)) / (height / 2);
		}
		else{
			worldY = -1 * ((ypos / (height / 2)) - 1);
		}

		cout << "WorldX: " << worldX << " WorldY: " << worldY << endl;

		mouseDragging = true;
	}

	//If mouse releases
	if (button == GLFW_MOUSE_BUTTON_LEFT	&& action == GLFW_RELEASE){
		mouseDragging = false;
	}
}
bool firstMouse = true;;
static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
	//if (firstMouse){
	//	lastCursorX = xpos;
	//	lastCursorY = ypos;
	//	firstMouse = false;
	//}
	////Calculate world position of cursor
	//int width, height;
	//glfwGetWindowSize(window, &width, &height);
	//
	//double worldX, worldY;
	//if (xpos > width / 2){
	//	worldX = (xpos - (width / 2)) / (width / 2);
	//}
	//else{
	//	worldX = (xpos / (width / 2)) - 1;
	//}
	//if (ypos > height / 2){
	//	worldY = (-1 * (ypos - height / 2)) / (height / 2);
	//}
	//else{
	//	worldY = -1 * ((ypos / (height / 2)) - 1);
	//}
	//float offsetX = xpos - lastCursorX;
	//float offsetY = lastCursorY - ypos;
	//
	//lastCursorX = xpos;
	//lastCursorY = ypos;
	//
	//float sensitivity = .05f;
	//offsetX *= sensitivity;
	//offsetY *= sensitivity;
	//camera.turn(offsetX, offsetY);
	//yaw += offsetX;
	//pitch += offsetY;
	//vec3 front;
	//front.x = cos(radians(pitch)) * cos(radians(yaw));
	//front.y = sin(radians(pitch));
	//front.z = cos(radians(pitch)) * sin(radians(yaw));
	//
	//cameraFront = normalize(front);
}
static void error_callback(int error, const char* description)
{
	fputs(description, stderr);
}
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_Q && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);

	float currentTime = glfwGetTime();
	float deltaTime = currentTime - lastTime;
	lastTime = currentTime;
	float cameraSpeed = .2f * deltaTime;

	if (key == GLFW_KEY_W){
		//camera.pos += cameraSpeed * normalize(cameraFront);
	}
	if (key == GLFW_KEY_A){
		//camera.pos -= camera.getRight()*cameraSpeed;
	}
	if (key == GLFW_KEY_S){
		//camera.pos -= cameraSpeed * normalize(cameraFront);
	}
	if (key == GLFW_KEY_D){
		//camera.pos += camera.getRight()*cameraSpeed;
	}
}