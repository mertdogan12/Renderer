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
    /* GLFW */
    GLFWwindow *window;

    // Initialize the library
    if (!glfwInit())
    return -1;

    // Create a windowed mode window and its OpenGL context
    window = glfwCreateWindow(1920, 1080, "Renderer", NULL, NULL);
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

    // Objects
    float coord[] = { 100.0f, 100.0f };
    float coord2[] = { 600.0f, 100.0f };
    float coord3[] = { 100.0f, 600.0f };
    renderer::VertexObject vertexObject("test245x253", coord, 1.0f, 1.0f, "res/textures/test245x253.png");
    renderer::VertexObject vertexObject2("test571x840", coord2, 0.5f, 0.5f, "res/textures/test571x840.jpg");
    renderer::VertexObject vertexObject3("test500x500", coord3, 1.0f, 1.0f, "res/textures/test500x500.png");

    renderer::Renderer::map.insert({"test245x253", vertexObject});
    renderer::Renderer::map.insert({"test571x840", vertexObject2});
    renderer::Renderer::map.insert({"test500x500", vertexObject3});

    {
        bool print = true;

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
            GLCALL(glBindBuffer(GL_ARRAY_BUFFER, renderer::Renderer::vertexArray));
            GLCALL(glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(renderer::Vertex) * sizes.Verticies, vertecies));

            GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, renderer::Renderer::indicies));
            GLCALL(glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, sizeof(unsigned int) * sizes.Indices, indicies));

            /* Draws */
            GLCALL(glDrawElements(GL_TRIANGLES, sizes.Indices * sizes.Indices, GL_UNSIGNED_INT, (void*)0));

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
