#define GLEW_STATIC
#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include "iostream"
#include "fstream"
#include "unordered_map"
#include "cstring"
#include "string"
#include "memory"
#include "chrono"
#include "thread"

#include "Renderer.h"
#include "Shader.h"
#include "VertexObject.h"
#include "Encoder.h"

// TODO remove when not longern needed
#define hex(x) " " << std::hex << (unsigned int) (unsigned char) x

// Converts the fist 4 chars from the given arr. to an float.
// Returns the float.
float charsToFloat(const char* inp)
{
    float out;
    std::memcpy(&out, inp, 4);

    return out;
}

// Parses the Textures from the inp.
// Then creates the parsed textures
void parseTextures(std::string &inp, const int start)
{
    int offset = start;

    char id = inp[offset];
    offset++;

    float x = charsToFloat(inp.substr(offset, 4).c_str());
    float y = charsToFloat(inp.substr(offset + 4, 4).c_str());
    float scaleX = charsToFloat(inp.substr(offset + 4 * 2, 4).c_str());
    float scaleY = charsToFloat(inp.substr(offset + 4 * 3, 4).c_str());
    offset += 4 * 4;

    char pathLen = inp[offset];
    std::string path = inp.substr(offset + 1, pathLen);
    offset += 1 + pathLen;

    renderer::Renderer::map.insert({id, new renderer::VertexObject(x, y, scaleX, scaleY, path)});

    std::cout << "Texture loaded: " << (int) id << ", " << path << std::endl;

    if (inp[offset] == 0x0b)
        return;

    parseTextures(inp, offset);
}

int main() 
{
    /* GLFW */
    GLFWwindow *window;
    const unsigned int width = 1920, height = 1080;

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

    // Parse Data
    try
    {
        for (std::string line; std::getline(std::cin, line);)
        {
            parseTextures(line, 0);;
        }
    } catch(std::runtime_error& e)
    {
        std::cout << e.what() << std::endl;
        return -1;
    }

    // Encoder
    renderer::Encoder encoder("out.mp4", width, height);

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
