#define GLEW_STATIC
#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include "iostream"
#include "unordered_map"
#include "cstring"
#include "memory"
#include "chrono"
#include "thread"

#include "Renderer.h"
#include "Shader.h"
#include "VertexObject.h"
#include "Encoder.h"

int main() 
{
    /* GLFW */
    GLFWwindow *window;
    unsigned int width = 1920, height = 1080;

    // Initialize the library
    if (!glfwInit())
    return -1;

    // Create a windowed mode window and its OpenGL context
    window = glfwCreateWindow(width, height, "Renderer", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    // GLFW hints
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Make the window's context current
    glfwMakeContextCurrent(window);

    glfwSwapInterval(1);

    try 
    {
        renderer::Init();
    } catch (std::exception e)
    {
        std::cout << e.what() << std::endl;
        return -1;
    }

    // Encoder
    renderer::Encoder encoder("out.mp4", width, height);

    // Objects
    renderer::VertexObject vertexObject("test245x253", 0.0f, 100.0f, 1.0f, 1.0f, "res/textures/test245x253.png");
    renderer::VertexObject vertexObject2("test571x840", 600.0f, 100.0f, 0.5f, 0.5f, "res/textures/test571x840.jpg");
    renderer::VertexObject vertexObject3("test500x500", 100.0f, 600.0f, 1.0f, 1.0f, "res/textures/test500x500.png");

    vertexObject2.ChangeCoords();

    renderer::Renderer::map.insert({"test245x253", &vertexObject});
    renderer::Renderer::map.insert({"test571x840", &vertexObject2});

    renderer::Renderer::map["test571x840"]->ChangeCoords();

    {
        bool print = true;
        float x = 0.0f, scale = 0.0f;

        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
        {
            /* Render here */
            renderer::Renderer::clear();

            /* Parses the map into vertecies and indicies */
            renderer::SizeStruct sizes = renderer::Renderer::calcCount();

            renderer::Vertex vertecies[sizes.Verticies];
            unsigned int indicies[sizes.Indices];
            renderer::Renderer::parseObjects(vertecies, indicies);

            /* ChangeCoords */
            renderer::Renderer::map["test245x253"]->ChangeCoords(x);
            renderer::Renderer::map["test571x840"]->ChangeCoords(renderer::VertexObject::DEFAULT, x, scale, scale);

            x += 1.0f;
            scale += 0.001f;

            if (x > 1080)
            {
                x = 0.0f;
                scale = 0.0f;
            }

            renderer::Draw(1920.0f, 1080.0f, sizes, vertecies, indicies);

            /* Swap front and back buffers */
            glfwSwapBuffers(window);

            /* Poll for and process events */
            glfwPollEvents();

            /* Pixels to video */
            int pixelsSize = width * height * 3; 
            GLbyte *pixels = new GLbyte[pixelsSize];
            GLCALL(glReadPixels(0, 0, (float) width, (float) height, GL_RGB, GL_BYTE, pixels));

            encoder.Write(pixels, pixelsSize);

            free(pixels);
        }
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
} 
