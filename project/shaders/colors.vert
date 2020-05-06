#version 330 core

// input
layout (location = 0) in vec3 xPos;
layout (location = 1) in vec3 xNormal;

layout (location = 3) in vec2 xTexCoords;


// input uniform
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;


// output
out vec3 normal;
out vec3 fragPos;
out vec2 TexCoords;


void main()
{



	gl_Position = projection * view * model * vec4(xPos, 1.0);


		
	normal = mat3(transpose(inverse(model))) * xNormal;  
	fragPos = vec3(model * vec4(xPos, 1.0));
	TexCoords = xTexCoords;

}