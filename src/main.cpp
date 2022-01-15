#define GLEW_STATIC
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "iostream"
#include "unordered_map"
#include "cstring"

#include "Renderer.h"
#include "Shader.h"
#include "VertexObject.h"

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

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    glfwSwapInterval(1);

    GLenum err = glewInit();
    if (err != GLEW_OK)
    std::cout << "Glew Error" << std::endl;

    renderer::Init();

    std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;

    // Objects
    float coord[] = { 100.0f, 100.0f };
    float coord2[] = { 600.0f, 100.0f };
    float coord3[] = { 100.0f, 600.0f };
    renderer::VertexObject vertexObject("test", coord, 245.0f, 253.0f, "res/textures/test.png");
    renderer::VertexObject vertexObject2("test2", coord2, 245.0f, 253.0f, "res/textures/test.png");
    renderer::VertexObject vertexObject3("test3", coord3, 245.0f, 253.0f, "res/textures/test.png");

    renderer::Renderer::map.insert({"test", vertexObject});
    renderer::Renderer::map.insert({"test2", vertexObject2});
    renderer::Renderer::map.insert({"test3", vertexObject3});

    // Vertex Array
    unsigned int rendererID;
    GLCALL(glGenBuffers(1, &rendererID));
    GLCALL(glBindBuffer(GL_ARRAY_BUFFER, rendererID));
    GLCALL(glBufferData(GL_ARRAY_BUFFER, sizeof(renderer::Vertex) * 1000, nullptr, GL_DYNAMIC_DRAW));

    // Coords
    GLCALL(glEnableVertexAttribArray(1));
    GLCALL(glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(renderer::Vertex), (const void*)offsetof(renderer::Vertex, Coords)));

    // Rgba
    GLCALL(glEnableVertexAttribArray(2));
    GLCALL(glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(renderer::Vertex), (const void*)offsetof(renderer::Vertex, Rgba)));

    // TexCoords
    GLCALL(glEnableVertexAttribArray(3));
    GLCALL(glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(renderer::Vertex), (const void*)offsetof(renderer::Vertex, TexCoords)));

    // TextureIndex
    GLCALL(glEnableVertexAttribArray(4));
    GLCALL(glVertexAttribPointer(4, 1, GL_FLOAT, GL_FALSE, sizeof(renderer::Vertex), (const void*)offsetof(renderer::Vertex, TextureIndex)));

    unsigned int elementbuffer;
    GLCALL(glGenBuffers(1, &elementbuffer));
    GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer));
    GLCALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * 1000, nullptr, GL_DYNAMIC_DRAW));

    {
        bool print = true;

        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
        {
            /* Render here */
            renderer::Renderer::Clear();

            /* Parses the map into vertecies and indicies */
            renderer::SizeStruct sizes = renderer::Renderer::CalcCount();

            renderer::Vertex vertecies[sizes.Verticies];
            unsigned int indicies[sizes.Indices];
            renderer::Renderer::ParseObjects(vertecies, indicies);

            /* Prints the vertecies */
            if (print)
            {
                std::cout << std::endl << "Render Data" << std::endl;

                for (int i = 0; i < sizes.Verticies; i++)
                {
                    // Coords
                    for (int j = 0; j < 2; j++)
                        std::cout << vertecies[i].Coords[j] << " ";
                    std::cout << " | ";

                    // Rgba
                    for (int j = 0; j < 4; j++)
                        std::cout << vertecies[i].Rgba[j] << " ";
                    std::cout << " | ";

                    // TexCoords
                    for (int j = 0; j < 2; j++)
                        std::cout << vertecies[i].TexCoords[j] << " ";
                    std::cout << " | ";

                    // TextureIndex
                    std::cout << vertecies[i].TextureIndex << std::endl;
                }

                std::cout << std::endl;

                for (int i = 0; i < sizes.Indices; i++)
                {
                    std::cout << indicies[i] << " ";
                }

                std::cout << std::endl;

                print = false;
            }

            /* MVP */
            glm::mat4 proj = glm::ortho(0.0f, 1920.0f, 0.0f, 1080.0f, -1.0f, 1.0f);
            glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
            glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));

            glm::mat4 mvp = proj;
            renderer::Renderer::shader->SetUniformMat4f("u_MVP", mvp);

            /* Write Buffer */
            GLCALL(glBindBuffer(GL_ARRAY_BUFFER, rendererID));
            GLCALL(glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(renderer::Vertex) * sizes.Verticies, vertecies));

            GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer));
            GLCALL(glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, sizeof(unsigned int) * sizes.Indices, indicies));

            /* Draws */
            GLCALL(glDrawElements(GL_TRIANGLES, sizes.Indices * 6, GL_UNSIGNED_INT, (void*)0));

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
