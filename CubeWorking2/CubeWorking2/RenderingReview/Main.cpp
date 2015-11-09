#include<glew.h>
#include<glfw3.h>
#include "ShaderHelpers.h"
#include<SOIL.h>
#include "Camera.h"
using namespace std;
#include<vector>
#include<string>
#include<sstream>

GLuint bufferIndex;
GLuint arrayIndex;
GLint programIndex;

const GLsizei numVertices = 5;
const GLsizei numComponents = numVertices * 5;
vec3 currentPosition;
vec3 currentScale;
float rotationAngle;
vec3 rotationAxis;
mat4 worldMatrix;

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

	vec3 currentPosition = vec3(0, 0, 0);
	vec3 currentScale = vec3(1, 1, 1);
	float rotationAngle = 0;
	vec3 rotationAxis = vec3(0, 0, 1);

	glGenVertexArrays(1, &arrayIndex);
	glBindVertexArray(arrayIndex);

	vector<GLfloat> modelVertices = loadOBJ("cube2.obj");
	GLfloat modelVertices2[288];
	for (int i = 0; i < modelVertices.size(); i++){

		modelVertices2[i] = modelVertices[i];
	}

	glGenBuffers(1, &bufferIndex);
	glBindBuffer(GL_ARRAY_BUFFER, bufferIndex);

	glBufferData(
		GL_ARRAY_BUFFER,
		sizeof(modelVertices2),
		modelVertices2,
		GL_STATIC_DRAW);

	glVertexAttribPointer(
		0,
		3,
		GL_FLOAT,
		GL_FALSE,
		sizeof(GL_FLOAT) * 8,
	0);
	glEnableVertexAttribArray(0);
	
	 
	GLuint textureID = SOIL_load_OGL_texture(
		"archer.jpg", SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glVertexAttribPointer(
		2,
		2,
		GL_FLOAT,
		GL_FALSE,
		sizeof(GL_FLOAT) * 8,
		(void*)(sizeof(GL_FLOAT) * 3));
	glEnableVertexAttribArray(2);

	glVertexAttribPointer(
		3,
		3,
		GL_FLOAT,
		GL_FALSE,
		sizeof(GL_FLOAT) * 8,
		(void*)(sizeof(GL_FLOAT) *5));
	glEnableVertexAttribArray(3);

	glClearColor(0.392f, 0.584f, 0.929f, 1.0f);

	programIndex = loadShaderProgram("Shaders/vertexShader.glsl", "Shaders/fragmentShader.glsl");
	if (programIndex) {
		glUseProgram(programIndex);
	}

	setShaderColor(programIndex, "color", 1, 0, 1);
	worldMatrix = translate(currentPosition) * scale(currentScale) * rotate(rotationAngle, rotationAxis);
	setShaderMatrix(programIndex, "worldMatrix", worldMatrix);

}

void update() {
	/*
	vec3 cameraTarget = vec3(0.0f, 0.0f, 0.0f);
	vec3 cameraDirection = normalize(cameraPos - cameraTarget);
	
	vec3 up = vec3(0.0f, 1.0f, 0.0f);
	vec3 cameraRight = normalize(cross(up, cameraDirection));

	cameraUp = vec3(0.0f, 1.0f, 0.0f);
	*/

	camera.getForward();
	camera.getRight();
	camera.getUp();

	GLfloat radius = 1.0f;
	GLfloat camX = sin(glfwGetTime())* radius;
	GLfloat camZ = cos(glfwGetTime())* radius;

	mat4 viewMatrix = lookAt(camera.pos, camera.getLookAt(), vec3(0.0f, 1.0f, 0.0f));
	//mat4 viewMatrix = lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
	//mat4 perspectiveMatrix = glm::perspective(3.14f/2.0f, 800.0f / 800.0f, .001f, 1000.0f);
	mat4 perspectiveMatrix = glm::perspective(100.0f, 1.0f, 0.01f, 1000.0f);
	perspectiveMatrix *= viewMatrix;
	setShaderMatrix(programIndex, "cameraMatrix", perspectiveMatrix);
	cout << cameraPos.x << "  " << cameraPos.y <<  endl;
	
}

void draw() {
	//cout<<"Drawing"<<endl;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnableVertexAttribArray(0);
	glBindVertexArray(arrayIndex);
	glDrawArrays(
		GL_TRIANGLES,
		0,
		numCubeVertices);
	glFlush();


}  

vector<GLfloat> loadOBJ(const char* filename)
{
	vector<float> outVertices;
	vector<vec2> uvs;
	vector<vec3> vertices;
	vector<vec3> normals;

	ifstream in(filename, ios::in);
	if (!in)
	{
		cerr << "Cannot open " << filename << endl; exit(1);
	}

	string line;
	while (getline(in, line))
	{

		if (line.substr(0, 2) == "v "){
			istringstream s(line.substr(2));
			vec3 vertex;
			s >> vertex.x;
			s >> vertex.y;
			s >> vertex.z;
			vertices.push_back(vertex);
		}
		else if (line.substr(0, 2) == "vn"){
			istringstream s(line.substr(2));
			vec3 normal;
			s >> normal.x;
			s >> normal.y;
			s >> normal.z;
			normals.push_back(normal);
		}
		else if (line.substr(0, 2) == "vt"){
			istringstream s(line.substr(2));
			vec2 uv;
			s >> uv.x;
			s >> uv.y;
			uvs.push_back(uv);
		}
		else if (line.substr(0, 2) == "f ")
		{
			istringstream s(line.substr(2));
			GLushort a, b, c;
			char temp;
			s >> a;
			s >> temp;
			s >> b;
			s >> temp;
			s >> c;

			cout << a << "/" << b << "/" << c << endl;

			a--; 
			b--; 
			c--;
			outVertices.push_back(vertices[a].x);
			outVertices.push_back(vertices[a].y);
			outVertices.push_back(vertices[a].z);

			outVertices.push_back(uvs[b].x);
			outVertices.push_back(uvs[b].y);

			outVertices.push_back(normals[c].x);
			outVertices.push_back(normals[c].y);
			outVertices.push_back(normals[c].z);

			s >> a; s >> temp; s >> b; s >> temp; s >> c;
			cout << a << "/" << b << "/" << c << endl;
			a--; b--; c--;
			outVertices.push_back(vertices[a].x);
			outVertices.push_back(vertices[a].y);
			outVertices.push_back(vertices[a].z);

			outVertices.push_back(uvs[b].x);
			outVertices.push_back(uvs[b].y);

			outVertices.push_back(normals[c].x);
			outVertices.push_back(normals[c].y);
			outVertices.push_back(normals[c].z);

			s >> a; s >> temp; s >> b; s >> temp; s >> c;
			cout << a << "/" << b << "/" << c << endl;
			a--; b--; c--;
			outVertices.push_back(vertices[a].x);
			outVertices.push_back(vertices[a].y);
			outVertices.push_back(vertices[a].z);

			outVertices.push_back(uvs[b].x);
			outVertices.push_back(uvs[b].y);

			outVertices.push_back(normals[c].x);
			outVertices.push_back(normals[c].y);
			outVertices.push_back(normals[c].z);
		}
	}
	return outVertices;
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
	if (firstMouse){
		lastCursorX = xpos;
		lastCursorY = ypos;
		firstMouse = false;
	}
	//Calculate world position of cursor
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
	float offsetX = xpos - lastCursorX;
	float offsetY = lastCursorY - ypos;

	lastCursorX = xpos;
	lastCursorY = ypos;

	float sensitivity = .05f;
	offsetX *= sensitivity;
	offsetY *= sensitivity;
	camera.turn(offsetX, offsetY);
	yaw += offsetX;
	pitch += offsetY;
	vec3 front;
	front.x = cos(radians(pitch)) * cos(radians(yaw));
	front.y = sin(radians(pitch));
	front.z = cos(radians(pitch)) * sin(radians(yaw));

	cameraFront = normalize(front);
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
		camera.pos += cameraSpeed * normalize(cameraFront);
	}
	if (key == GLFW_KEY_A){
		camera.pos -= camera.getRight()*cameraSpeed;
	}
	if (key == GLFW_KEY_S){
		camera.pos -= cameraSpeed * normalize(cameraFront);
	}
	if (key == GLFW_KEY_D){
		camera.pos += camera.getRight()*cameraSpeed;
	}
}