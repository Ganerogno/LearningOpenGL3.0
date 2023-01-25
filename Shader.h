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
	void AddShader(std::string path, GLenum flag);
	void CreateProgram();
public:
	Shader(std::string path, bool isVert, bool isFrag);
	void Use();
	static void UseBaseShader();
	GLuint GetProgram();
};