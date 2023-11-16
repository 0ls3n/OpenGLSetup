#include "ShaderHandler.h"

unsigned int ShaderHandler::CompileShader(unsigned int type, const std::string& source)
{
    unsigned int id = glCreateShader(type); // Creating the shader instance into the unsigned int
    const char* src = source.c_str(); // Creating a variable that holds the source file in a memory address
    glShaderSource(id, 1, &src, nullptr); // Replaces the source code in a shader object with our shader source
    glCompileShader(id); // Compiling the shader created

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result); // Returns the GL_COMPILE_STATUS to the result integer
    if (result == GL_FALSE)
    {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* message = (char*)alloca(length * sizeof(char));
        glGetShaderInfoLog(id, length, &length, message);
        std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << "shader!" << std::endl;
        std::cout << message << std::endl;

        glDeleteShader(id);
        return 0;
    }

    return id; // Returns the shader we created
}


unsigned int ShaderHandler::CreateShader(const std::string& vertexFileSource, const std::string& fragmentFileSource)
{
    unsigned int program = glCreateProgram(); // Creating a new instance of a openGL Shader Program

    const std::string& vertexShader = ParseShader(vertexFileSource); // Calling a function we made, that parses shader from .shader to string
    const std::string& fragmentShader = ParseShader(fragmentFileSource);

    // Calling the CompileShader function, so it creates two instances of shaders, vertex and fragment shaders
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

    // Attaching the shaders to the program we created
    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    // When we attached the shaders to the program, the shader instances are of no use. So we delete them (Memory efficient)
    glDeleteShader(vs);
    glDeleteShader(fs);

    return program; // Returns the program we created
}

std::string ShaderHandler::ParseShader(const std::string& sourceFile)
{
    std::ifstream stream(sourceFile); // Creating an instance of an ifstream, which reads from files

    std::string line;
    std::stringstream ss;
    while (std::getline(stream, line))
    {
        ss << line << '\n';
    }

    return ss.str();
}

