#pragma once

#include <glad\glad.h>

#include <string>
#include <fstream>
#include <iostream>



class Shader
{
public:
	Shader();

	void CompileShader(const char* vertexShaderLocation, const char* fragmentShaderLocation);

	void UseShader();

	/*
	
	void setBool();
	void setInt();
	void setFloat();

	~Shader();
	*/

	int getUniformLocation(const char* uniformName);


private:

	unsigned int shaderProgramID;

	std::string ReadFile(const char* filePath);

	void checkCompileErrors(unsigned int shader, std::string type);
};