#version 330 core

// input
layout (location = 0) in vec3 xPos;



// input uniform
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;




// output


void main()
{

	gl_Position = projection * view * model * vec4(xPos, 1.0);

}