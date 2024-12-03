#include "Shader.h"

Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
	// shader
	unsigned int vertexShader, fragmentShader;
	// ¥ÌŒÛ–≈œ¢¥Ú”°
	char infoLog[512];
	int success;

	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexPath, NULL);
	glCompileShader(vertexShader);

	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << infoLog << std::endl;
	}

	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentPath, NULL);
	glCompileShader(fragmentShader);
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << infoLog << std::endl;
	}

	ID = glCreateProgram();
	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);
	glLinkProgram(ID);
	glGetProgramiv(ID, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(ID, 512, NULL, infoLog);
		std::cout << infoLog << std::endl;
	}
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void Shader::use()
{
	glUseProgram(ID);
}

void Shader::setBool(const std::string& name, bool value) const
{
	int uniformLocation = glGetUniformLocation(ID, name.c_str());
	if (uniformLocation == -1)
	{
		std::cout << "ERROR::CANNOT FIND THE UNIFORM" << std::endl;
	}
	glUniform1i(uniformLocation, (int)value);

}

void Shader::setInt(const std::string& name, int value) const
{
	int uniformLocation = glGetUniformLocation(ID, name.c_str());
	if (uniformLocation == -1)
	{
		std::cout << "ERROR::CANNOT FIND THE UNIFORM" << std::endl;
	}
	glUniform1i(uniformLocation, value);
}

void Shader::setFloat(const std::string& name, float value) const
{
	int uniformLocation = glGetUniformLocation(ID, name.c_str());
	if (uniformLocation == -1)
	{
		std::cout << "ERROR::CANNOT FIND THE UNIFORM" << std::endl;
	}
	glUniform1f(uniformLocation, value);
}
