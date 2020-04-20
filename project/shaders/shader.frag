#version 330 core


uniform sampler2D textureA;
uniform sampler2D textureB;
uniform float mixValue;

in vec2 TexCoord;



out vec4 FragColor;
//uniform vec4 myColor;





void main()
{
	
	FragColor = vec4(1.0f, 0.0f, 0.0f, 1.0f);
	//FragColor = texture(textureA, TexCoord);
}