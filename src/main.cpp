#define GLEW_STATIC
#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include "iostream"
#include "fstream"
#include "unordered_map"
#include "cstring" 
#include "string" 
#include "chrono"
#include "thread"

#include "renderer/Renderer.h"
#include "renderer/Shader.h"
#include "renderer/VertexObject.h"
#include "renderer/Encoder.h"

int main() 
{ 
    std::ofstream rawVideo;  
    rawVideo.open("out.raw", std::ios::binary | std::ios::out);

    const float width = 1920.0f, height = 1080.0f;

    /* GLFW */
    GLFWwindow *window;

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

    /* Renderer */
    try 
    {
        renderer::Init();
    } catch (std::runtime_error e)
    {
        std::cout << "Error while initing the renderer" << std::endl;
        std::cout << e.what() << std::endl;
        return -1;
    }
    
    renderer::VertexObject pic1(0, 0, 1, 1, "res/textures/test571x840.jpg");
    renderer::VertexObject pic2(0, 0, 1, 1, "res/textures/test245x253.png");
    
    renderer::Renderer::map.insert({0, &pic1});
    renderer::Renderer::map.insert({1, &pic2});

    // Encoder
    // renderer::Encoder encoder("out.mp4", width, height);

    {
        float x = 0.0f, scale = 0.0f;
        int count = 0;

        /* Loop until the user closes the window */
        while (true)
        {
            /* Render here */
            renderer::Renderer::clear();

            /* Parses the map into vertecies and indicies */
            renderer::SizeStruct sizes = renderer::Renderer::calcCount();

            renderer::Vertex vertecies[sizes.Verticies];
            unsigned int indicies[sizes.Indices];
            renderer::Renderer::parseObjects(vertecies, indicies);

            /* ChangeCoords */
            renderer::Renderer::map[0]->ChangeCoords(x);
            renderer::Renderer::map[1]->ChangeCoords(renderer::VertexObject::DEFAULT, renderer::VertexObject::DEFAULT,
                    scale, scale);

            x += 1.0f;
            scale += 0.001f;

            if (x > 1080)
            {
                x = 0.0f;
                scale = 0.0f;
            }

            renderer::Draw(width, height, sizes, vertecies, indicies);

            /* Swap front and back buffers */
            glfwSwapBuffers(window);

            /* Poll for and process events */
            glfwPollEvents();

            /* Pixels to video */
            int pixelsSize = width * height * 3; 
            GLbyte *pixels = new GLbyte[pixelsSize];
            GLCALL(glReadPixels(0, 0, width, height, GL_RGB, GL_UNSIGNED_BYTE, pixels));

            rawVideo.write((char*) pixels, pixelsSize);

            // encoder.Write(pixels, pixelsSize);

            free(pixels);

            /* Count */
            if (count >= 60 * 20)
            {
                std::cout << "STOP ------------- STOP" << std::endl;
                break;
            }

            count++;
        }
    }

    rawVideo.close();

    glfwDestroyWindow(window);
    // glfwTerminate(true);

    return 0;
} 
