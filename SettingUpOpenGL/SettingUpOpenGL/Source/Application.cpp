#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "ShaderHandler.h"

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
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

    float positions[6] =
    {
        -0.5f, -0.5f,
         0.0f,  0.5f,
         0.5f, -0.5f
    };

    unsigned int vbo; // Creating an unsigned int which is holding the vertex buffer object (VBO)
    glGenBuffers(1, &vbo); // Generates the buffer, with reference to the VBO
    glBindBuffer(GL_ARRAY_BUFFER, vbo); // Defining which GL_ARRAY_BUFFER that is active
    glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), positions, GL_STATIC_DRAW); // Defining the data in the active buffer

    unsigned int vao; // Creating an unsigned int which is holding the vertex array object (VAO)
    glGenVertexArrays(1, &vao); // Generates a vertex array object with referece to the VAO
    glBindVertexArray(vao); // Defining which VAO that is active

    glEnableVertexAttribArray(0); // Enabling 
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, NULL);

    

    unsigned int shader = ShaderHandler::CreateShader("Shaders/vertex.glsl", "Shaders/fragment.glsl");
    

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glUseProgram(shader);
        glBindVertexArray(vao);

        glDrawArrays(GL_TRIANGLES, 0, 3);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }
    
    glDeleteProgram(shader);

    glfwTerminate();
    return 0;
}
