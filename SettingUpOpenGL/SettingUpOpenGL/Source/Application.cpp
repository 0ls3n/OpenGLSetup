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
    window = glfwCreateWindow(800, 600, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }
    
    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    glfwSwapInterval(1);

    if (glewInit() != GLEW_OK)
    {
        std::cout << "Error" << std::endl;
    }

    
    float points[8]
    {
        -0.5f, -0.5f, // 0
        0.5f, -0.5f,  // 1
        0.5f, 0.5f,   // 2
        -0.5f, 0.5f   // 3
    };

    float colors[12]
    {
        1.0, 0.0, 0.0,
        0.0, 1.0, 0.0,
        0.0, 0.0, 1.0,
        1.0, 0.0, 1.0
    };

    unsigned int indices[6]
    {
        0, 1, 2,
        2, 3, 0
    };

    unsigned int points_vbo;
    glGenBuffers(1, &points_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
    glBufferData(GL_ARRAY_BUFFER, 8 * sizeof(float), points, GL_STATIC_DRAW);

    unsigned int color_vbo;
    glGenBuffers(1, &color_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, color_vbo);
    glBufferData(GL_ARRAY_BUFFER, 12 * sizeof(float), colors, GL_STATIC_DRAW);

    unsigned int vao = 0;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, NULL);

    glBindBuffer(GL_ARRAY_BUFFER, color_vbo);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    
    unsigned int ibo;
    glGenBuffers(1, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), indices, GL_STATIC_DRAW);

    
    unsigned int shader = ShaderHandler::CreateShader("Shaders/FirstShader/vertex.glsl", "Shaders/FirstShader/fragment.glsl");
    glUseProgram(shader);

    glBindAttribLocation(shader, 0, "position");
    glBindAttribLocation(shader, 1, "colors");

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0.1, 0.1, 0.1, 1);
        
        glBindVertexArray(vao);

       
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

        

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
