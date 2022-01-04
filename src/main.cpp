#define GLEW_STATIC
#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include "iostream"
#include "unordered_map"

#include "Renderer.h"
#include "VertexObject.h"

int main() 
{
    GLFWwindow *window;
    std::unordered_map<std::string, renderer::VertexObject> map;

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

    float coord[] = { 100.0f, 100.0f };
    renderer::VertexObject vertexObject("test", coord, 245.0f, 253.0f, "res/textures/test.png");

    map.insert({"test", vertexObject});

    // Vertex Array
    unsigned int rendererID;
    GLCALL(glGenBuffers(1, &rendererID));
    GLCALL(glBindBuffer(GL_ARRAY_BUFFER, rendererID));
    GLCALL(glBufferData(GL_ARRAY_BUFFER, sizeof(renderer::Vertex), nullptr, GL_DYNAMIC_DRAW));

    GLCALL(glEnableVertexAttribArray(1));
    GLCALL(glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(renderer::Vertex), (const void*)offsetof(renderer::Vertex, Coords)));

    GLCALL(glEnableVertexAttribArray(2));
    GLCALL(glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(renderer::Vertex), (const void*)offsetof(renderer::Vertex, Coords)));

    GLCALL(glEnableVertexAttribArray(3));
    GLCALL(glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(renderer::Vertex), (const void*)offsetof(renderer::Vertex, Coords)));

    GLCALL(glEnableVertexAttribArray(4));
    GLCALL(glVertexAttribPointer(4, 1, GL_FLOAT, GL_FALSE, sizeof(renderer::Vertex), (const void*)offsetof(renderer::Vertex, Coords)));

    // Indices
    unsigned int indicies[] =
    {
        0, 1, 2, 2, 3, 1,
        4, 5, 6, 6, 5, 4
    };


    renderer::Renderer renderer;
    {
        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
        {
            /* Render here */
            renderer.Clear();

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
