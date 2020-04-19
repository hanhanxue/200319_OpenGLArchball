#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <iostream>

#include <glad\glad.h>
#include <GLFW\glfw3.h>


#include <fstream>
#include <string>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


//#include <sstream>
//#include <iostream>

#include "shader.h"
#include "camera.h"




void hhx_cursor_callback(GLFWwindow* window, double xpos, double ypos);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void keyCallbackFunction(GLFWwindow* window, int key, int scancode, int action, int mods);



float mixValue = 0.0f;
float radius = 10.0f;

float pitch = 0.0f;
float yaw = -90.0f;

bool mouseFirstMove = true;

// Camera
glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 5.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

int keyW = 0;
int keyS = 0;
int keyA = 0;
int keyD = 0;

float deltaTime = 0.0f;
float lastFrame = 0.0f;




Camera camera;
Shader haha;



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




	// glad: load all OpenGL function pointers
	if (    !gladLoadGLLoader(GLADloadproc(glfwGetProcAddress))     )
	{
		std::cout << "Failed to initialize GLAD." << std::endl;
		return -1;
	}


	haha.CompileShader("shaders/shader.vert", "shaders/shader.frag");

	// Actual framebuffer size
	glViewport(50, 50, 500, 500);

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);


	glfwSetCursorPosCallback(window, hhx_cursor_callback);


	glfwSetKeyCallback(window, keyCallbackFunction);


	/*
		float verticesTriangleA[] = {
 0.5f,  0.5f, 0.0f,       1.0f, 0.0f, 0.0f,       1.0f, 1.0f,// top right
 0.5f, -0.5f, 0.0f,       0.0f, 1.0f, 0.0f,       1.0f, 0.0f,// bottom right
-0.5f, -0.5f, 0.0f,       0.0f, 0.0f, 1.0f,       0.0f, 0.0f,// bottom left
-0.5f,  0.5f, 0.0f,       0.0f, 0.0f, 1.0f,       0.0f, 1.0f,// top left
	};
	*/


	float vertices[] = {
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	};


	unsigned int indices[] = {  // note that we start from 0!
		0, 1, 3,   // first triangle
		1, 2, 3    // second triangle
	};


	glm::vec3 cubePositions[] = {
  glm::vec3(0.0f,  0.0f,  0.0f),
  glm::vec3(2.0f,  5.0f, -15.0f),
  glm::vec3(-1.5f, -2.2f, -2.5f),
  glm::vec3(-3.8f, -2.0f, -12.3f),
  glm::vec3(2.4f, -0.4f, -3.5f),
  glm::vec3(-1.7f,  3.0f, -7.5f),
  glm::vec3(1.3f, -2.0f, -2.5f),
  glm::vec3(1.5f,  2.0f, -2.5f),
  glm::vec3(1.5f,  0.2f, -1.5f),
  glm::vec3(-1.3f,  1.0f, -1.5f)
	};





	unsigned int VAO[2], VBO[2], EBO[2];

	glGenVertexArrays(2, VAO);
	glGenBuffers(2, VBO);
	glGenBuffers(2, EBO);



	glBindVertexArray(VAO[0]);

	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[0]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	//glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	//glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);













	unsigned int textureA;
	glGenTextures(1, &textureA);
	glBindTexture(GL_TEXTURE_2D, textureA);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height, nChannels;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load("textures/container.jpg", &width, &height, &nChannels, 0);
	if (data)
	{	
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
		printf("Texture A loaded successfully\n");
	}
	else
	{
		printf("Failed to load texture A\n");
	}



	unsigned int textureB;
	glGenTextures(1, &textureB);
	glBindTexture(GL_TEXTURE_2D, textureB);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	//int width, height, nChannels;
	data = stbi_load("textures/awesomeface.png", &width, &height, &nChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
		printf("Texture B loaded successfully\n");
	}
	else
	{
		printf("Failed to load texture B\n");
	}


	glBindTexture(GL_TEXTURE_2D, 0);
	stbi_image_free(data);










	


	glEnable(GL_PROGRAM_POINT_SIZE);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	int location = haha.getUniformLocation("myColor");











	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, textureA);

	glActiveTexture(GL_TEXTURE4);
	glBindTexture(GL_TEXTURE_2D, textureB);

	unsigned int locaA = haha.getUniformLocation("textureA");
	unsigned int locaB = haha.getUniformLocation("textureB");
	unsigned int locMix = haha.getUniformLocation("mixValue");








	haha.UseShader();

	glm::mat4 trans = glm::mat4(1.0f);



	trans = glm::rotate(trans, (float)glfwGetTime(), glm::vec3(0.0, 0.0, 1.0));
	trans = glm::translate(trans, glm::vec3(0.5f, -0.5f, 0.0f));

	std::cout << trans[0][0] << std::endl;







	glm::mat4 model = glm::mat4(1.0f);
	model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));

	//glm::mat4 view = glm::mat4(1.0f);
	//view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
		
	glm::mat4 projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

	unsigned int modelLoc = haha.getUniformLocation("model");
	unsigned int viewLoc = haha.getUniformLocation("view");
	unsigned int projectionLoc = haha.getUniformLocation("projection");



	
	glEnable(GL_DEPTH_TEST);




	while (!glfwWindowShouldClose(window)) // This is the render loop
	{
		// input

		float currentFrame = glfwGetTime();
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


		//glUseProgram(shaderProgram);
	





		glUniform1i(locaA, 2);
		glUniform1i(locaB, 4);

		glUniform4f(location, 0.0f, 1.0f, 0.0f, 1.0f);
		glUniform1f(locMix, mixValue);


		glBindVertexArray(VAO[0]);
		
		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		for (unsigned int i = 0; i < 10; i++)
		{
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, cubePositions[i]);
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, &model[0][0]);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}

		float camX, camZ;
		//float radius = 10.0f;
		camX = sin(glfwGetTime()) * radius;
		camZ = cos(glfwGetTime()) * radius;
		glm::mat4 view = glm::mat4(1.0f);
        //view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));





		view = camera.GetViewMatrix();







		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, &model[0][0]);
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);
		glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, &projection[0][0]);


		


		// check and call events and swap the buffers
		glfwSwapBuffers(window);
		//glfwPollEvents();
		glfwPollEvents();
	}


	glfwTerminate();
	return 0;
} 


void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	if (width > height)
	{
		glViewport(0, 0, width, height * width / height);
	}
	else
	{
		glViewport(0, 0, height, height);
	}

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

