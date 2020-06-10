#define STB_IMAGE_IMPLEMENTATION

#include <iostream>

#include <glad\glad.h>

#include <GLFW\glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
//#include <glm/gtc/type_ptr.hpp>

#include "stb_image.h"
#include "shader.h"
#include "cameraEuler.h"

const unsigned int SCR_WIDTH = 1280;
const unsigned int SCR_HEIGHT = 720;

double deltaTime = 0.0;
double lastFrameTime = 0.0;

void hhx_framebuffer_size_callback(GLFWwindow* window, int width, int height);
void hhx_cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
void hhx_mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
void hhx_key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

bool mouse_button_left_pressed = false;
bool mouse_button_middle_pressed = false;
bool mouse_button_right_pressed = false;

bool mouse_first_move = true;

bool CTRL = false;
bool ALT = false;
bool SHIFT = false;

double last_xpos = 0.0;
double last_ypos = 0.0;

glm::vec3 lightPos(1.2f, 1.0f, 2.0f);


//Camera camera;
cameraEuler camera = cameraEuler(SCR_WIDTH - 50.0f, SCR_HEIGHT - 50.0f);

Shader shader_default;
Shader shader_light;
Shader shader_lamp;



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
	glfwSetCursorPosCallback(window, hhx_cursor_position_callback);
	glfwSetMouseButtonCallback(window, hhx_mouse_button_callback);
	glfwSetKeyCallback(window, hhx_key_callback);




	// glad: load all OpenGL function pointers
	if (    !gladLoadGLLoader(GLADloadproc(glfwGetProcAddress))     )
	{
		std::cout << "Failed to initialize GLAD." << std::endl;
		return -1;
	}




	glViewport(25, 25, SCR_WIDTH - 50, SCR_HEIGHT - 50);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glPointSize(10.0f);

























	float viewPivot[] = {
		0.0f, 0.0f, 0.0f,
	};

	unsigned int pivotVAO;
	unsigned int pivotVBO;
	glGenVertexArrays(1, &pivotVAO);
	glGenBuffers(1, &pivotVBO);



	glBindVertexArray(pivotVAO);

	glBindBuffer(GL_ARRAY_BUFFER, pivotVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(viewPivot), viewPivot, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);






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






	float vertices[] = {
		// positions          // normals           // texture coords
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
	};





	unsigned int newBox_VAO;
	unsigned int newBox_VBO;
	glGenVertexArrays(1, &newBox_VAO);
	glGenBuffers(1, &newBox_VBO);

	glBindVertexArray(newBox_VAO);

	glBindBuffer(GL_ARRAY_BUFFER, newBox_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(3);



	unsigned int light_VAO;
	glGenVertexArrays(1, &light_VAO);

	glBindVertexArray(light_VAO);

	//glBindBuffer(GL_ARRAY_BUFFER, newBox_VBO);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);



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


	glm::vec3 axisColors[] = {
	glm::vec3(1.0f, 0.0f, 0.0f),
	glm::vec3(0.0f, 1.0f, 0.0f),
	glm::vec3(0.0f, 0.0f, 1.0f),
	};



	glm::vec3 pointLightPositions[] = {
	glm::vec3(0.7f,  0.2f,  2.0f),
	glm::vec3(2.3f, -3.3f, -4.0f),
	glm::vec3(-4.0f,  2.0f, -12.0f),
	glm::vec3(0.0f,  0.0f, -3.0f)
	};









	int width, height, nrChannels;
	unsigned char* data = stbi_load("textures/container.jpg", &width, &height, &nrChannels, 0);

	unsigned int myTexture;
	glGenTextures(1, &myTexture);
	glBindTexture(GL_TEXTURE_2D, myTexture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);





	data = stbi_load("textures/container2_specular.png", &width, &height, &nrChannels, 0);

	unsigned int myTextureSpec;
	glGenTextures(1, &myTextureSpec);
	glBindTexture(GL_TEXTURE_2D, myTextureSpec);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);




	glActiveTexture(GL_TEXTURE3);
	glBindTexture(GL_TEXTURE_2D, myTexture);

	glActiveTexture(GL_TEXTURE5);
	glBindTexture(GL_TEXTURE_2D, myTextureSpec);








	shader_default.CompileShader("shaders/shader.vert", "shaders/shader.frag");
	unsigned int model_Loc = shader_default.getUniformLocation("model");
	unsigned int view_Loc = shader_default.getUniformLocation("view");
	unsigned int projection_Loc = shader_default.getUniformLocation("projection");
	unsigned int myColor_Loc = shader_default.getUniformLocation("myColor");





	shader_lamp.CompileShader("shaders/lamp.vert", "shaders/lamp.frag");
	unsigned int lamp_model_Loc = shader_lamp.getUniformLocation("model");
	unsigned int lamp_view_Loc = shader_lamp.getUniformLocation("view");
	unsigned int lamp_projection_Loc = shader_lamp.getUniformLocation("projection");

	unsigned int lamp_lampClr_Loc = shader_lamp.getUniformLocation("lampClr");





	shader_light.CompileShader("shaders/colors.vert", "shaders/colors.frag");
	unsigned int light_model_Loc = shader_light.getUniformLocation("model");
	unsigned int light_view_Loc = shader_light.getUniformLocation("view");
	unsigned int light_projection_Loc = shader_light.getUniformLocation("projection");
	//unsigned int light_objectColor_Loc = shader_light.getUniformLocation("objectColor");
	unsigned int light_lightColor_Loc = shader_light.getUniformLocation("lightColor");
	unsigned int light_lightPos_Loc = shader_light.getUniformLocation("lightPos");
	unsigned int light_viewPos_Loc = shader_light.getUniformLocation("viewPos");

	unsigned int light_ambientClr_Loc = shader_light.getUniformLocation("material.ambientClr");
	unsigned int light_diffuseClr_Loc = shader_light.getUniformLocation("material.diffuseClr");
	unsigned int light_specularClr_Loc = shader_light.getUniformLocation("material.specularClr");
	unsigned int light_shininess_Loc = shader_light.getUniformLocation("material.shininess");
	unsigned int light_diffuseTexture_Loc = shader_light.getUniformLocation("material.diffuseTexture");
	unsigned int light_specTexture_Loc = shader_light.getUniformLocation("material.specTexture");


	/*
		unsigned int light_LambientClr_Loc = shader_light.getUniformLocation("light.ambientClr");
	unsigned int light_LdiffuseClr_Loc = shader_light.getUniformLocation("light.diffuseClr");
	unsigned int light_LspecularClr_Loc = shader_light.getUniformLocation("light.specularClr");
	unsigned int light_Lposition_Loc = shader_light.getUniformLocation("light.position");
	unsigned int light_Ldirection_Loc = shader_light.getUniformLocation("light.direction");

	unsigned int light_Lconstant_Loc = shader_light.getUniformLocation("light.k_constant");
	unsigned int light_Llinear_Loc = shader_light.getUniformLocation("light.k_linear");
	unsigned int light_Lquadratic_Loc = shader_light.getUniformLocation("light.k_quadratic");

	unsigned int light_LcutOff_Loc = shader_light.getUniformLocation("light.cutOff");
	unsigned int light_LcutOffOuter_Loc = shader_light.getUniformLocation("light.cutOffOuter");

	*/

	// dirLight
	unsigned int dirLight_direction_Loc = shader_light.getUniformLocation("dirLight.direction");
	unsigned int dirLight_ambient_Loc = shader_light.getUniformLocation("dirLight.ambient");
	unsigned int dirLight_diffuse_Loc = shader_light.getUniformLocation("dirLight.diffuse");
	unsigned int dirLight_specular_Loc = shader_light.getUniformLocation("dirLight.specular");


	// pointLight 0
	unsigned int pointLight0_posiion_Loc = shader_light.getUniformLocation("pointLights[0].position");

	unsigned int pointLight0_ambient_Loc = shader_light.getUniformLocation("pointLights[0].ambient");
	unsigned int pointLight0_diffuse_Loc = shader_light.getUniformLocation("pointLights[0].diffuse");
	unsigned int pointLight0_specular_Loc = shader_light.getUniformLocation("pointLights[0].specular");

	unsigned int pointLight0_kconstant_Loc = shader_light.getUniformLocation("pointLights[0].k_constant");
	unsigned int pointLight0_klinear_Loc = shader_light.getUniformLocation("pointLights[0].k_linear");
	unsigned int pointLight0_kquadratic_Loc = shader_light.getUniformLocation("pointLights[0].k_quadratic");


	// pointLight 1
	unsigned int pointLight1_posiion_Loc = shader_light.getUniformLocation("pointLights[1].position");

	unsigned int pointLight1_ambient_Loc = shader_light.getUniformLocation("pointLights[1].ambient");
	unsigned int pointLight1_diffuse_Loc = shader_light.getUniformLocation("pointLights[1].diffuse");
	unsigned int pointLight1_specular_Loc = shader_light.getUniformLocation("pointLights[1].specular");

	unsigned int pointLight1_kconstant_Loc = shader_light.getUniformLocation("pointLights[1].k_constant");
	unsigned int pointLight1_klinear_Loc = shader_light.getUniformLocation("pointLights[1].k_linear");
	unsigned int pointLight1_kquadratic_Loc = shader_light.getUniformLocation("pointLights[1].k_quadratic");

	// SpotLight

	unsigned int spotLight_position_Loc = shader_light.getUniformLocation("spotLight.position");
	unsigned int spotLight_cutoff_Loc = shader_light.getUniformLocation("spotLight.cutoff");
	unsigned int spotLight_direction_Loc = shader_light.getUniformLocation("spotLight.direction");
	unsigned int spotLight_cutoffOuter_Loc = shader_light.getUniformLocation("spotLight.cutoffOuter");

	unsigned int spotLight_ambient_Loc = shader_light.getUniformLocation("spotLight.ambient");
	unsigned int spotLight_diffuse_Loc = shader_light.getUniformLocation("spotLight.diffuse");
	unsigned int spotLight_specular_Loc = shader_light.getUniformLocation("spotLight.specular");

	unsigned int spotLight_kconstant_Loc = shader_light.getUniformLocation("spotLight.k_constant");
	unsigned int spotLight_klinear_Loc = shader_light.getUniformLocation("spotLight.k_linear");
	unsigned int spotLight_kquadratic_Loc = shader_light.getUniformLocation("spotLight.k_quadratic");

	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 projection = glm::mat4(1.0f);


	//glPolygonMode(GL_POINT);


	while (!glfwWindowShouldClose(window)) // This is the render loop
	{

		//printf("mouseButtonLeft: %i\n", mouse_button_left_pressed);
		//printf("CTRL: %i, ALT: %i, SHIFT: %i\n", CTRL, ALT, SHIFT);

		double currentFrameTime = glfwGetTime();
		deltaTime = currentFrameTime - lastFrameTime;
		lastFrameTime = currentFrameTime;
		//printf("deltaTime: %f\n", deltaTime);





		// rendering commands here
		//glClearColor(1.0f, 0.8f, 0.8f, 1.0f);    // state setting
		//glClearColor(0.8471f, 0.7373f, 0.7843f, 1.0f);    // state setting
		glClearColor(0.5373f, 0.2706f, 0.9098f, 1.0f);    // state setting
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);           // state using





		//camera.updateCamera(1.0f, 0.0f);
		model = glm::mat4(1.0f);
		view = camera.getViewMatrix();
		projection = camera.getProjectionMatrix();





		shader_default.UseShader();
		glUniformMatrix4fv(model_Loc, 1, GL_FALSE, &model[0][0]);
		glUniformMatrix4fv(view_Loc, 1, GL_FALSE, &view[0][0]);
		glUniformMatrix4fv(projection_Loc, 1, GL_FALSE, &projection[0][0]);
		// NONE PRO glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));

		// Pivot
		if ((mouse_button_left_pressed || mouse_button_middle_pressed || mouse_button_right_pressed)
			&& (CTRL || ALT))
		{
			model = camera.getPivotMatrix();
			glUniformMatrix4fv(model_Loc, 1, GL_FALSE, &model[0][0]);

			glUniform4f(myColor_Loc, 1.0f, 1.0f, 1.0f, 1.0f);
			glBindVertexArray(pivotVAO);
			glDrawArrays(GL_POINTS, 0, 1);

			model = glm::mat4(1.0f);
			glUniformMatrix4fv(model_Loc, 1, GL_FALSE, &model[0][0]);
		}
		// Grid
		glUniform4f(myColor_Loc, 0.5f, 0.5f, 0.5f, 1.0f);
		for (unsigned int i = 0; i < 8; i++)
		{
			glBindVertexArray(GridVAO[i]);
			glDrawArrays(GL_LINES, 0, 2);
		}

		for (unsigned int i = 0; i < 3; i++)
		{
			glUniform4f(myColor_Loc, axisColors[i].x, axisColors[i].y, axisColors[i].z, 1.0f);
			glBindVertexArray(VAO[i]);
			glDrawArrays(GL_LINES, 0, 2);
		}
		// Box Background
		glUniform4f(myColor_Loc, 0.1f, 0.1f, 0.1f, 1.0f);
		//glUniform4f(myColor_Loc, 0.0f, 0.0f, 0.0f, 1.0f);
		glBindVertexArray(BoxVAO);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);




		//float pos = sin(glfwGetTime());
		//model = glm::translate(model, glm::vec3(0.0f, pos, 0.0f));
		glm::vec3 lightColor = glm::vec3(1.0f, 1.0f, 1.0f);
		glm::vec3 diffuseColor = lightColor * glm::vec3(0.5f);
		glm::vec3 ambientColor = diffuseColor * glm::vec3(0.2f);






		// Light Bulbs
		shader_lamp.UseShader();

		for (unsigned int i = 0; i < 4; i++)
		{
			model = glm::translate(model, pointLightPositions[i]);
			model = glm::scale(model, glm::vec3(0.08f));

			glUniformMatrix4fv(lamp_model_Loc, 1, GL_FALSE, &model[0][0]);
			glUniformMatrix4fv(lamp_view_Loc, 1, GL_FALSE, &view[0][0]);
			glUniformMatrix4fv(lamp_projection_Loc, 1, GL_FALSE, &projection[0][0]);
			glUniform3fv(lamp_lampClr_Loc, 1, &lightColor[0]);

			glBindVertexArray(newBox_VAO);
			glDrawArrays(GL_TRIANGLES, 0, 36);

			model = glm::mat4(1.0f);

		}








		shader_light.UseShader();
		glUniformMatrix4fv(light_model_Loc, 1, GL_FALSE, &model[0][0]);
		glUniformMatrix4fv(light_view_Loc, 1, GL_FALSE, &view[0][0]);
		glUniformMatrix4fv(light_projection_Loc, 1, GL_FALSE, &projection[0][0]);

		glUniform3f(light_lightColor_Loc, 1.0f, 1.0f, 1.0f);


		glUniform3fv(light_viewPos_Loc, 1, &camera.getPositionVec()[0]);

		//glUniform3f(light_ambientClr_Loc, 1.0f, 0.5f, 0.31f);
		//glUniform3f(light_diffuseClr_Loc, 1.0f, 0.5f, 0.31f);
		glUniform3f(light_specularClr_Loc, 0.5f, 0.5f, 0.5f);
		glUniform1f(light_shininess_Loc, 32.0f);
		glUniform1i(light_diffuseTexture_Loc, 3);
		glUniform1i(light_specTexture_Loc, 5);
	

		/*
				glUniform3fv(light_LambientClr_Loc, 1, &ambientColor[0]);
		glUniform3fv(light_LdiffuseClr_Loc, 1, &diffuseColor[0]);
		glUniform3fv(light_LspecularClr_Loc, 1, &lightColor[0]);
		//glUniform3fv(light_Lposition_Loc, 1, &lightPos[0]);
		glUniform3fv(light_Lposition_Loc, 1, &camera.getPositionVec()[0]);


		//glUniform3f(light_Ldirection_Loc, -0.2f, -1.0f, -0.3f);
		glUniform3fv(light_Ldirection_Loc, 1, &camera.getFrontVec()[0]);

		glUniform1f(light_Lconstant_Loc, 1.0f);
		glUniform1f(light_Llinear_Loc, 0.09f);
		glUniform1f(light_Lquadratic_Loc, 0.032f);

		glUniform1f(light_LcutOff_Loc, glm::cos(  glm::radians(12.5f) ));
		glUniform1f(light_LcutOffOuter_Loc, glm::cos(glm::radians(15.5f)));

		*/

		glUniform3f(dirLight_direction_Loc, -0.2f, -1.0f, -0.3f);
		glUniform3f(dirLight_ambient_Loc, 0.05f, 0.05f, 0.05f);
		glUniform3f(dirLight_diffuse_Loc, 0.4f, 0.4f, 0.4f);
		glUniform3f(dirLight_specular_Loc, 0.5f, 0.5f, 0.5f);


		// POINT LIGHT
		glUniform3fv(pointLight0_posiion_Loc, 1, &pointLightPositions[0][0]);

		glUniform3f(pointLight0_ambient_Loc, 0.05f, 0.05f, 0.05f);
		glUniform3f(pointLight0_diffuse_Loc, 0.8f, 0.8f, 0.8f);
		glUniform3f(pointLight0_specular_Loc, 1.0f, 1.0f, 1.0f);

		glUniform1f(pointLight0_kconstant_Loc, 1.0f);
		glUniform1f(pointLight0_klinear_Loc, 0.09f);
		glUniform1f(pointLight0_kquadratic_Loc, 0.032f);


		glUniform3fv(pointLight1_posiion_Loc, 1, &pointLightPositions[1][0]);

		glUniform3f(pointLight1_ambient_Loc, 0.05f, 0.05f, 0.05f);
		glUniform3f(pointLight1_diffuse_Loc, 0.8f, 0.8f, 0.8f);
		glUniform3f(pointLight1_specular_Loc, 1.0f, 1.0f, 1.0f);

		glUniform1f(pointLight1_kconstant_Loc, 1.0f);
		glUniform1f(pointLight1_klinear_Loc, 0.09f);
		glUniform1f(pointLight1_kquadratic_Loc, 0.02f);


		// SPOT LIGHT
		glUniform3fv(spotLight_position_Loc, 1, &camera.getPositionVec()[0]);
		glUniform3fv(spotLight_direction_Loc, 1, &camera.getFrontVec()[0]);


		glUniform1f(spotLight_cutoff_Loc, glm::cos(glm::radians(12.5f)));
		glUniform1f(spotLight_cutoffOuter_Loc, glm::cos(glm::radians(17.5f)));

		glUniform3f(spotLight_ambient_Loc, 0.05f, 0.05f, 0.05f);
		glUniform3f(spotLight_diffuse_Loc, 0.8f, 0.8f, 0.8f);
		glUniform3f(spotLight_specular_Loc, 1.0f, 1.0f, 1.0f);

		glUniform1f(spotLight_kconstant_Loc, 1.0f);
		glUniform1f(spotLight_klinear_Loc, 0.09f);
		glUniform1f(spotLight_kquadratic_Loc, 0.032f);


		glBindVertexArray(newBox_VAO);
		for (unsigned int i = 0; i < 10; i++)
		{
			model = glm::mat4(1.0f);
			model = glm::translate(model, cubePositions[i]);

			float angle = 20.0f * i;
			model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
			glUniformMatrix4fv(light_model_Loc, 1, GL_FALSE, &model[0][0]);

			glDrawArrays(GL_TRIANGLES, 0, 36);

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
	glViewport(25, 25, width - 50, height - 50);
	camera.setAspectRatio(width - 50.0f, height - 50.0f);
}

void hhx_cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (mouse_first_move)
	{
		last_xpos = xpos;
		last_ypos = ypos;
		mouse_first_move = false;
	}

	float delta_xpos = (float)(xpos - last_xpos);
	float delta_ypos = (float)(last_ypos - ypos);

	last_xpos = xpos;
	last_ypos = ypos;

	if (ALT && mouse_button_left_pressed)
	{
		camera.tumble(delta_xpos, delta_ypos);
	}

	if (ALT && mouse_button_middle_pressed)
	{

		camera.track(delta_xpos, delta_ypos);
	}

	if (ALT && mouse_button_right_pressed)
	{
		if (CTRL)
		{
			camera.zoom(delta_xpos, delta_ypos);
		}
		else
		{
			camera.dolly(delta_xpos, delta_ypos);
		}

	}

	
	//printf("delta_xpos: %f, delta_ypos: %f\n", delta_xpos, delta_ypos);
}

void hhx_mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
	{
		mouse_button_left_pressed = true;
	}
	else
	{
		mouse_button_left_pressed = false;
	}

	if (button == GLFW_MOUSE_BUTTON_MIDDLE && action == GLFW_PRESS)
	{
		mouse_button_middle_pressed = true;
	}
	else
	{
		mouse_button_middle_pressed = false;
	}

	if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
	{
		mouse_button_right_pressed = true;
	}
	else
	{
		mouse_button_right_pressed = false;
	}
}

void hhx_key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_H && action == GLFW_PRESS)
	{
		camera.home();
	}

	CTRL = false;
	ALT = false;
	SHIFT = false;

	if (mods == GLFW_MOD_CONTROL)
	{
		CTRL = true;
	}


	if (mods == GLFW_MOD_ALT)
	{
		ALT = true;
	}


	if (mods == GLFW_MOD_SHIFT)
	{
		SHIFT = true;
	}

	if (mods == (GLFW_MOD_CONTROL | GLFW_MOD_ALT))
	{
		CTRL = true;
		ALT = true;
	}
	//printf("mods: %i bitwise: %i\n", mods, (GLFW_MOD_CONTROL | GLFW_MOD_ALT)  );

}


