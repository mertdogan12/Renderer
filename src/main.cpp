#define GLEW_STATIC
#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include "iostream"

int main() 
{
    GLFWwindow *window;

    /* Initialize the library */
    if (!glfwInit())
    return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(1920, 1080, "Renderer", NULL, NULL);
    if (!window)
    {
    glfwTerminate();
    return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    glfwSwapInterval(1);

    GLenum err = glewInit();
    if (err != GLEW_OK)
    std::cout << "Glew Error" << std::endl;

    std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;

    {
        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
        {
            /* Render here */
            glClear(GL_COLOR_BUFFER_BIT);

            /* Swap front and back buffers */
            glfwSwapBuffers(window);

            /* Poll for and process events */
            glfwPollEvents();
        }
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
} 
