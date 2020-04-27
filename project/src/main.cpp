#define STB_IMAGE_IMPLEMENTATION

#include <iostream>
//#include <fstream>
//#include <string>

#include <algorithm>
#include <glad\glad.h>
#include <GLFW\glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "stb_image.h"
#include "shader.h"
#include "camera.h"


void hhx_framebuffer_size_callback(GLFWwindow* window, int width, int height);

double hhx_toCameraCoord(double screenCoord, int scrDimension);

glm::vec3 hhx_getArcballSrfPt(double xScreen, double yScreen);

double deltaTime = 0.0;
double lastFrame = 0.0;


const unsigned int SCR_WIDTH = 1280;
const unsigned int SCR_HEIGHT = 720;

glm::mat4 viewCur = glm::mat4(1.0f);
glm::mat4 viewLast = glm::mat4(1.0f);

bool archball_on = false;
double cursorPos_last_X;
double cursorPos_last_Y;
double cursorPos_cur_X;
double cursorPos_cur_Y;

void hhx_CursorPosCallback(GLFWwindow* window, double xpos, double ypos);
void hhx_MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);


void hhx_cursor_callback(GLFWwindow* window, double xpos, double ypos);
void keyCallbackFunction(GLFWwindow* window, int key, int scancode, int action, int mods);



float mixValue = 0.0f;
float radius = 10.0f;

float pitch = 0.0f;
float yaw = -90.0f;

bool mouseFirstMove = true;

// Camera


int keyW = 0;
int keyS = 0;
int keyA = 0;
int keyD = 0;



Camera camera;
Shader shader_axis;



int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Window size
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Bamn Acros", nullptr, nullptr);
	if (window == nullptr)
	{
		std::cout << "Failed to created GLFW window." << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);


	glfwSetFramebufferSizeCallback(window, hhx_framebuffer_size_callback);
	//glfwSetCursorPosCallback(window, hhx_cursor_callback);
	glfwSetCursorPosCallback(window, hhx_CursorPosCallback);
	glfwSetMouseButtonCallback(window, hhx_MouseButtonCallback);

	glfwSetKeyCallback(window, keyCallbackFunction);


	//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);










	// glad: load all OpenGL function pointers
	if (    !gladLoadGLLoader(GLADloadproc(glfwGetProcAddress))     )
	{
		std::cout << "Failed to initialize GLAD." << std::endl;
		return -1;
	}



	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glViewport(25, 25, SCR_WIDTH - 50, SCR_HEIGHT - 50);
















	float gridX1[] = {
		-5.0f, 0.0f, -5.0f,
		5.0f, 0.0f, -5.0f,
	};
	float gridX2A[] = {
	-5.0f, 0.0f, -0.0f,
	-0.1f, 0.0f, -0.0f,
	};
	float gridX2B[] = {
1.1f, 0.0f, -0.0f,
5.0f, 0.0f, -0.0f,
	};
	float gridX3[] = {
	-5.0f, 0.0f, 5.0f,
	5.0f, 0.0f, 5.0f,
	};


	float gridZ1[] = {
	-5.0f, 0.0f, -5.0f,
	-5.0f, 0.0f, 5.0f,
	};
	float gridZ2A[] = {
	0.0f, 0.0f, -5.0f,
	0.0f, 0.0f, -0.1f,
	};
	float gridZ2B[] = {
0.0f, 0.0f, 1.1f,
0.0f, 0.0f, 5.0f,
	};
	float gridZ3[] = {
	5.0f, 0.0f, -5.0f,
	5.0f, 0.0f, 5.0f,
	};

	// Left X Axis
	unsigned int GridVAO[8];
	unsigned int GridVBO[8];
	glGenVertexArrays(8, GridVAO);
	glGenBuffers(8, GridVBO);



	glBindVertexArray(GridVAO[0]);

	glBindBuffer(GL_ARRAY_BUFFER, GridVBO[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(gridX1), gridX1, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);



	glBindVertexArray(GridVAO[1]);

	glBindBuffer(GL_ARRAY_BUFFER, GridVBO[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(gridX2A), gridX2A, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindVertexArray(GridVAO[2]);

	glBindBuffer(GL_ARRAY_BUFFER, GridVBO[2]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(gridX2B), gridX2B, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);




	glBindVertexArray(GridVAO[3]);

	glBindBuffer(GL_ARRAY_BUFFER, GridVBO[3]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(gridX3), gridX3, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindVertexArray(GridVAO[4]);

	glBindBuffer(GL_ARRAY_BUFFER, GridVBO[4]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(gridZ1), gridZ1, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);



	glBindVertexArray(GridVAO[5]);

	glBindBuffer(GL_ARRAY_BUFFER, GridVBO[5]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(gridZ2A), gridZ2A, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindVertexArray(GridVAO[6]);

	glBindBuffer(GL_ARRAY_BUFFER, GridVBO[6]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(gridZ2B), gridZ2B, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);



	glBindVertexArray(GridVAO[7]);

	glBindBuffer(GL_ARRAY_BUFFER, GridVBO[7]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(gridZ3), gridZ3, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);



	float vertices_leftXAxis[] = {
		0.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
	};
	float vertices_upYAxis[] = {
		0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
	};
	float vertices_frontZAxis[] = {
		0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f,
	};

	// Left X Axis
	unsigned int VAO[3];
	unsigned int VBO[3];
	glGenVertexArrays(3, VAO);
	glGenBuffers(3, VBO);



	glBindVertexArray(VAO[0]);

	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_leftXAxis), vertices_leftXAxis, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);




	glBindVertexArray(VAO[1]);

	glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_upYAxis), vertices_upYAxis, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);





	glBindVertexArray(VAO[2]);

	glBindBuffer(GL_ARRAY_BUFFER, VBO[2]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_frontZAxis), vertices_frontZAxis, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);


	float vertices_box[] = {
		25.0f, -25.0f, 25.0f,    //front right 0
		-25.0f, -25.0f, 25.0f,   //front left  1
		-25.0f, -25.0f, -25.0f,   // back left 2
		25.0f, -25.0f, -25.0f,    //back right 3

		25.0f, 25.0f, 25.0f,    //front right  4
		-25.0f, 25.0f, 25.0f,   //front left   5
		-25.0f, 25.0f, -25.0f,   // back left  6
		25.0f, 25.0f, -25.0f,    //back right  7
	};

	unsigned int indices_box[] = {
		0, 1, 2, 
		2, 3, 0, 

		4, 5, 6, 
		6, 7, 4,

		0, 1, 5, 
		5, 4, 0,

		3, 2, 6, 
		6, 7, 3,

		1, 2, 6,
		6, 5, 1,

		0, 3, 7,
		7, 4, 0,
	};


	unsigned int BoxVAO;
	unsigned int BoxVBO;
	unsigned int BoxEBO;

	glGenVertexArrays(1, &BoxVAO);
	glGenBuffers(1, &BoxVBO);
	glGenBuffers(1, &BoxEBO);

	glBindVertexArray(BoxVAO);

	glBindBuffer(GL_ARRAY_BUFFER, BoxVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_box), vertices_box, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, BoxEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices_box), indices_box, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);





















	shader_axis.CompileShader("shaders/shader.vert", "shaders/shader.frag");
	shader_axis.UseShader();

	unsigned int model_Loc = shader_axis.getUniformLocation("model");
	unsigned int view_Loc = shader_axis.getUniformLocation("view");
	unsigned int projection_Loc = shader_axis.getUniformLocation("projection");

	unsigned int axisColor_Loc = shader_axis.getUniformLocation("axisColor");

	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);

	glm::vec3 axisColors[] = {
		glm::vec3(1.0f, 0.0f, 0.0f),
		glm::vec3(0.0f, 1.0f, 0.0f),
		glm::vec3(0.0f, 0.0f, 1.0f),
	};


	view = camera.GetViewMatrix();

	while (!glfwWindowShouldClose(window)) // This is the render loop
	{
		/*
				printf("on: %i  lasX: %f  lasY:%f  curX: %f  curY: %f\n", 
			archball_on,
			cursorPos_last_X,
			cursorPos_last_Y,
			cursorPos_cur_X,
			cursorPos_cur_Y
		);
		*/
		float angle = 0.0f;
		glm::vec3 rotationAxis;

		if (archball_on)
		{
			if (cursorPos_cur_X != cursorPos_last_X || cursorPos_cur_Y != cursorPos_last_Y) {


				glm::vec3 OP1 = hhx_getArcballSrfPt(cursorPos_last_X, cursorPos_last_Y);
				glm::vec3 OP2 = hhx_getArcballSrfPt(cursorPos_cur_X, cursorPos_cur_Y);

				angle = acos(std::min(1.0f, glm::dot(OP1, OP2)));

				rotationAxis = glm::cross(OP1, OP2);


				view = glm::rotate(viewLast, angle, rotationAxis);





			}


		}



		viewCur = view;

		printf("angle: %f\n", angle);

		// input

		double currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;






		// rendering commands here
		glClearColor(1.0f, 0.8f, 0.8f, 1.0f);    // state setting
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);           // state using



		glUniformMatrix4fv(model_Loc, 1, GL_FALSE, &model[0][0]);
		glUniformMatrix4fv(view_Loc, 1, GL_FALSE, &view[0][0]);
		glUniformMatrix4fv(projection_Loc, 1, GL_FALSE, &projection[0][0]);




		glUniform4f(axisColor_Loc, 0.5f, 0.5f, 0.5f, 1.0f);
		for (unsigned int i = 0; i < 8; i++)
		{
			glBindVertexArray(GridVAO[i]);
			glDrawArrays(GL_LINES, 0, 2);
		}

		for (unsigned int i = 0; i < 3; i++)
		{
			glUniform4f(axisColor_Loc, axisColors[i].x, axisColors[i].y, axisColors[i].z, 1.0f);
			glBindVertexArray(VAO[i]);
			glDrawArrays(GL_LINES, 0, 2);
		}



		glUniform4f(axisColor_Loc, 0.1f, 0.1f, 0.1f, 1.0f);
		glBindVertexArray(BoxVAO);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);










		


		// check and call events and swap the buffers
		glfwSwapBuffers(window);
		//glfwPollEvents();
		glfwPollEvents();
	}


	glfwTerminate();
	return 0;
} 




































void hhx_framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.

		glViewport(0 + 50, 0 + 50, width - 50, height - 50);

}






float lastX;// = 400.0f;
float lastY;// = 300.0f;



void hhx_cursor_callback(GLFWwindow* window, double xpos, double ypos)
{
	//printf("xpos: %f, ypos: %f\n", xpos, ypos);
	//printf("lastX: %f, lastY: %f\n", lastX, lastY);

	//printf("mouseFirstMove: %d\n", mouseFirstMove);
	


	if (mouseFirstMove)
	{
		lastX = xpos;
		lastY = ypos;
		mouseFirstMove = false;
	}


	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos;

	lastX = xpos;
	lastY = ypos;
	//printf("xpos: %f, ypos: %f\n", xpos, ypos);

	camera.UpdateFront(xoffset, yoffset);

}











void keyCallbackFunction(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (GLFW_PRESS == action)
	{
		//printf("something pressed\n");
	}
	if (GLFW_KEY_UP == key && GLFW_PRESS == action)
	{
		radius += 0.5f;
		if (mixValue < 1.0f)
		{
			mixValue += 0.1f;
		}

	}
	if (GLFW_KEY_DOWN == key && GLFW_PRESS == action)
	{
		radius -= 0.5f;
		if (mixValue > 0.01f)
		{
			mixValue -= 0.1f;
		}

	}
	if (GLFW_KEY_ESCAPE == key && GLFW_PRESS == action)
	{
		glfwSetWindowShouldClose(window, true);

	}



	float cameraSpeed = 1.0f;
	if (GLFW_KEY_W == key && GLFW_PRESS == action)
	{
		keyW = 1;
	}
	else if (GLFW_KEY_W == key && GLFW_RELEASE == action)
	{
		keyW = 0;
	}
	if (GLFW_KEY_S == key && GLFW_PRESS == action)
	{
		keyS = 1;
	}
	else if (GLFW_KEY_S == key && GLFW_RELEASE == action)
	{
		keyS = 0;
	}
	if (GLFW_KEY_A == key && GLFW_PRESS == action)
	{
		keyA = 1;
	}
	else if (GLFW_KEY_A == key && GLFW_RELEASE == action)
	{
		keyA = 0;
	}
	if (GLFW_KEY_D == key && GLFW_PRESS == action)
	{
		keyD = 1;
	}
	else if (GLFW_KEY_D == key && GLFW_RELEASE == action)
	{
		keyD = 0;
	}


}





void hhx_CursorPosCallback(GLFWwindow* window, double xpos, double ypos)
{
	cursorPos_cur_X = xpos;
	cursorPos_cur_Y = ypos;
	//printf("xpos is: %f and ", xpos);
	//printf("ypos is: %f\n", ypos);
	


}


void hhx_MouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
	{
		//printf("Left Mouse");
		archball_on = true;
		cursorPos_last_X = cursorPos_cur_X;
		cursorPos_last_Y = cursorPos_cur_Y;
		//printf("brrrr");
		viewLast = viewCur;
	}
	else
	{
		archball_on = false;
	}

	if (button == GLFW_MOUSE_BUTTON_MIDDLE && action == GLFW_PRESS)
	{
		//printf("Middle Mouse");
	}

	if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
	{
		//printf("Right Mouse");
	}

}

double hhx_toCameraCoord(double screenCoord, int scrDimension)
{
	return screenCoord / (double)scrDimension * 2.0 - 1.0;
}


glm::vec3 hhx_getArcballSrfPt(double xScreen, double yScreen)
{

	float xCamera;
	float yCamera;
	float zCamera = 0.0;
	xCamera = hhx_toCameraCoord(xScreen, SCR_WIDTH);
	yCamera = -1.0 * hhx_toCameraCoord( yScreen, SCR_HEIGHT);

	float opSquared = xCamera * xCamera + yCamera * yCamera;

	glm::vec3 P = glm::vec3(xCamera, yCamera, zCamera);

	if (opSquared <= 1.0)
	{
		P.z = sqrt(1 - opSquared);
		
	}
	else
	{
		P = glm::normalize(P);
	}

	return P;
	//printf("xpos: %f and ypos: %f\n", x, y);

}