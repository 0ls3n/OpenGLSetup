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
	static unsigned int CreateShader(const std::string& vertexFileSource, const std::string& fragmentFileSource);

private:
	static unsigned int CompileShader(unsigned int type, const std::string& source);
	static std::string ParseShader(const std::string& sourceFile);
};