#version 330 core


uniform vec3 lampClr;


out vec4 hhxColor;


void main()
{
	hhxColor = vec4(lampClr, 1.0);

}