#include "shader.h"



Shader::Shader()
{
	shaderProgramID = 0;
}

void Shader::CompileShader(const char* vertexShaderLocation, const char* fragmentShaderLocation)
{
	unsigned int vertexShader, fragmentShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	shaderProgramID = glCreateProgram();

	std::string vertexShaderSource = ReadFile(vertexShaderLocation);
	const char* vertexShaderSourceC = vertexShaderSource.c_str();
	glShaderSource(vertexShader, 1, &vertexShaderSourceC, nullptr);
	glCompileShader(vertexShader);
	checkCompileErrors(vertexShader, "VERTEX");


	std::string fragmentShaderSource = ReadFile(fragmentShaderLocation);
	const char* fragmentShaderSourceC = fragmentShaderSource.c_str();
	glShaderSource(fragmentShader, 1, &fragmentShaderSourceC, nullptr);
	glCompileShader(fragmentShader);
	checkCompileErrors(fragmentShader, "FRAGMENT");


	glAttachShader(shaderProgramID, vertexShader);
	glAttachShader(shaderProgramID, fragmentShader);
	glLinkProgram(shaderProgramID);
	checkCompileErrors(shaderProgramID, "PROGRAM");

}

void Shader::UseShader()
{
	glUseProgram(shaderProgramID);
}



int Shader::getUniformLocation(const char* uniformName)
{
	return glGetUniformLocation(shaderProgramID, uniformName);
}









std::string Shader::ReadFile(const char* fileLocation)
{
	std::string content;

	std::ifstream fileStream;
	fileStream.open(fileLocation);

	if (!fileStream.is_open())
	{
		printf("Failed to read %s!", fileLocation);
		return "";
	}

	std::string line = "";
	while (!fileStream.eof())
	{
		std::getline(fileStream, line);
		content.append(line + "\n");
	}

	fileStream.close();
	return content;

}





// glvalidateProgram glGetProgramiv(GL_VALIDATE_STATUS)

void Shader::checkCompileErrors(unsigned int shader, std::string type)
{
	int success;
	char infoLog[1024];
	if (type != "PROGRAM")
	{
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
		}
	}
	else
	{
		glGetProgramiv(shader, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
		}
	}
}