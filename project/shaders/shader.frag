#version 330 core


uniform sampler2D textureA;
uniform sampler2D textureB;
uniform float mixValue;

in vec2 TexCoord;



out vec4 FragColor;
//uniform vec4 myColor;





void main()
{
	
	FragColor = mix(texture(textureA, TexCoord), texture(textureB, vec2(1.0 - TexCoord.x, TexCoord.y)), mixValue);
	//FragColor = texture(textureA, TexCoord);
}