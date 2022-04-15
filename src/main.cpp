#define GLEW_STATIC
#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include "iostream"
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

// Copies the given slice (start - end) to the buffer (buff[]).
// Returns the buffer (buff[])
template <typename T>
T* sliceArray(T inp[], T buff[], int start, int end)
{
    int len = end - start;

    for (int i = 0; i <= len; i++)
    {
        buff[i] = inp[start + i];
    }

    return buff;
}

// Converts the fist 4 chars from the given arr. to an float.
// Returns the float.
float charsToFloat(char* inp)
{
    float out = 0;
    std::memcpy(inp, &out, 4);

    return out;
}

void parseTextures(const char* inp, const int start)
{
    char buff[4];
    int offset = start;

    char id = inp[offset];
    offset++;

    float x = charsToFloat(sliceArray<char>((char*) inp, buff, offset, offset + 4));
    float y = charsToFloat(sliceArray<char>((char*) inp, buff, offset + 4, offset + 4 * 2));
    float scaleX = charsToFloat(sliceArray<char>((char*) inp, buff, offset + 4 * 2, offset + 4 * 3));
    float scaleY = charsToFloat(sliceArray<char>((char*) inp, buff, offset + 4 * 3, offset + 4 * 4));
    offset += 4 * 4 + 1;

    char pathLen = inp[offset];
    char pathBuff[pathLen];
    std::string path(sliceArray<char>((char*) inp, pathBuff, offset + 1, offset + 1 + pathLen));

    // static renderer::VertexObject obj(x, y, scaleX, scaleY, path);
    // renderer::Renderer::map.insert({id, &obj});
}

int main() 
{
    for (std::string line; std::getline(std::cin, line);)
    {
        const char* inp = line.c_str();
        parseTextures(inp, 0);;
    }

    return -1;

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
            renderer::Renderer::map[1]->ChangeCoords(renderer::VertexObject::DEFAULT, x, scale, scale);

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
