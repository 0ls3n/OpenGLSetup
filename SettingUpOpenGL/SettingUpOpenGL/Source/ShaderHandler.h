#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "ShaderProgram.h"

static class ShaderHandler 
{
public:
	static unsigned int CreateShader(const std::string& sourceFile);

private:
	static unsigned int CompileShader(unsigned int type, const std::string& source);
	static ShaderProgramSource ParseShader(const std::string& filePath);
};