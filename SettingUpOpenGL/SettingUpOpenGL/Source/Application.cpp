#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "ShaderHandler.h"

int main(void)
{

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_SAMPLES, 4);

    GLFWmonitor* mon = glfwGetPrimaryMonitor();
    const GLFWvidmode* mode = glfwGetVideoMode(mon);


    GLFWwindow* window;

    //window = glfwCreateWindow(mode->width, mode->height, "Hello World", mon, NULL);
    window = glfwCreateWindow(600, 600, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }
    
    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK)
    {
        std::cout << "Error" << std::endl;
    }

    
    float points[9]
    {
        0.0f, 0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f
    };

    float colours[9]
    {
        1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 1.0f
    };

    unsigned int points_vbo;
    glGenBuffers(1, &points_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
    glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float), points, GL_STATIC_DRAW);

    unsigned int colours_vbo;
    glGenBuffers(1, &colours_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, colours_vbo);
    glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float), colours, GL_STATIC_DRAW);

    unsigned int vao = 0;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    glBindBuffer(GL_ARRAY_BUFFER, colours_vbo);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);


    unsigned int shader = ShaderHandler::CreateShader("Shaders/FirstShader/vertex.glsl", "Shaders/FirstShader/fragment.glsl");
    
    glBindAttribLocation(shader, 0, "position");
    glBindAttribLocation(shader, 1, "vertex_colour");

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0.1, 0.1, 0.1, 1);
        glUseProgram(shader);
        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);


        if (GLFW_PRESS == glfwGetKey(window, GLFW_KEY_ESCAPE)) 
        {
            glfwSetWindowShouldClose(window, 1);
        }

        if (GLFW_PRESS == glfwGetKey(window, GLFW_KEY_R))
        {
            shader = ShaderHandler::CreateShader("Shaders/FirstShader/vertex.glsl", "Shaders/FirstShader/fragment.glsl");
            std::cout << "Updating shader..." << std::endl;
        }

        /* Poll for and process events */
        glfwPollEvents();
    }
    
    glDeleteProgram(shader);

    glfwTerminate();
    return 0;
}
