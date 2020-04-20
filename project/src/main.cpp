#define STB_IMAGE_IMPLEMENTATION

#include <iostream>
//#include <fstream>
//#include <string>

#include <glad\glad.h>
#include <GLFW\glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "stb_image.h"
#include "shader.h"
#include "camera.h"


void hhx_framebuffer_size_callback(GLFWwindow* window, int width, int height);

double deltaTime = 0.0;
double lastFrame = 0.0;










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
	GLFWwindow* window = glfwCreateWindow(800, 600, "Bamn Acros", nullptr, nullptr);
	if (window == nullptr)
	{
		std::cout << "Failed to created GLFW window." << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);


	glfwSetFramebufferSizeCallback(window, hhx_framebuffer_size_callback);
	glfwSetCursorPosCallback(window, hhx_cursor_callback);
	glfwSetKeyCallback(window, keyCallbackFunction);


	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);










	// glad: load all OpenGL function pointers
	if (    !gladLoadGLLoader(GLADloadproc(glfwGetProcAddress))     )
	{
		std::cout << "Failed to initialize GLAD." << std::endl;
		return -1;
	}



	glEnable(GL_DEPTH_TEST);












	float vertices_leftXAxis[] = {
		0.0f, 0.0f, 0.0f,
		10.0f, 0.0f, 0.0f,
	};
	float vertices_upYAxis[] = {
		0.0f, 0.0f, 0.0f,
		0.0f, 10.0f, 0.0f,
	};
	float vertices_frontZAxis[] = {
		0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 10.0f,
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










	shader_axis.CompileShader("shaders/shader.vert", "shaders/shader.frag");
	shader_axis.UseShader();
	unsigned int modelLoc = shader_axis.getUniformLocation("model");
	unsigned int viewLoc = shader_axis.getUniformLocation("view");
	unsigned int projectionLoc = shader_axis.getUniformLocation("projection");

	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

	while (!glfwWindowShouldClose(window)) // This is the render loop
	{
		// input

		double currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;




		float cameraSpeed = deltaTime * 2.5f;
		if (keyW == 1)
		{
			camera.UpdatePosition(FORWARD, deltaTime);
		}
		if (keyS == 1)
		{
			camera.UpdatePosition(BACKWARD, deltaTime);
		}
		if (keyA == 1)
		{
			camera.UpdatePosition(LEFT, deltaTime);
		}
		if (keyD == 1)
		{
			camera.UpdatePosition(RIGHT, deltaTime);
		}









		// rendering commands here
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);    // state setting
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);           // state using




		view = camera.GetViewMatrix();



		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, &model[0][0]);
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);
		glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, &projection[0][0]);








		for (unsigned int i = 0; i < 3; i++)
		{
			glBindVertexArray(VAO[i]);
			glDrawArrays(GL_LINES, 0, 2);
		}












		


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

		glViewport(0, 0, width, height);

}






float lastX;// = 400.0f;
float lastY;// = 300.0f;



void hhx_cursor_callback(GLFWwindow* window, double xpos, double ypos)
{
	printf("xpos: %f, ypos: %f\n", xpos, ypos);
	printf("lastX: %f, lastY: %f\n", lastX, lastY);

	printf("mouseFirstMove: %d\n", mouseFirstMove);
	


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
	printf("xpos: %f, ypos: %f\n", xpos, ypos);

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


	printf("mixValue is: %f\n", mixValue);
}

