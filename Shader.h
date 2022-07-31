#pragma once
#include <glad/glad.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

class Shader
{
	std::string shaderString;
public:
	GLuint program;
	Shader()
	{
		program = glCreateProgram();
	}
	Shader(const Shader& other)
	{
		program = other.program;
	}
	void AddShader(const GLchar* path, GLenum flag)
	{
		std::stringstream shaderStream;
		std::ifstream shaderFile;
		shaderFile.open(path);
		shaderStream << shaderFile.rdbuf();
		shaderFile.close();
		shaderString = shaderStream.str();

		GLuint shader;
		GLint succes;
		GLchar log[512];

		const GLchar* str = shaderString.c_str();
		shader = glCreateShader(flag);
		glShaderSource(shader, 1, &str, NULL);
		glCompileShader(shader);

		glGetShaderiv(shader, GL_COMPILE_STATUS, &succes);
		if (!succes)
		{
			glGetShaderInfoLog(shader, 512, NULL, log);
			std::cout << "Compile shader error path: "<< path << " error:" << log << std::endl;
		}
		glAttachShader(program, shader);
		glDeleteShader(shader);
	}
	void CreateProgram()
	{
		GLint succes;
		GLchar log[512];
		glLinkProgram(program);
		glGetProgramiv(program, GL_LINK_STATUS, &succes);
		if (!succes)
		{
			std::cout << "Link program error: " << log << std::endl;
		}
	}
	void Use()
	{
		glUseProgram(program);
	}
	static void UseBaseShader()
	{
		glUseProgram(0);
	}
};