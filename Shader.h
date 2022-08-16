#pragma once
#include <glad/glad.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

class Shader
{
	std::string shaderString;
	GLuint program;
public:
	Shader();
	Shader(const Shader& other);
	void AddShader(const GLchar* path, GLenum flag);
	void CreateProgram();
	void Use();
	static void UseBaseShader();
	GLuint GetProgram();
};