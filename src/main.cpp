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
    
    // Shader
    renderer::Shader shader("res/shaders/Basic.shader");
    shader.Bind();

    // Vertex Array
    unsigned int rendererID;
    GLCALL(glGenBuffers(1, &rendererID));
    GLCALL(glBindBuffer(GL_ARRAY_BUFFER, rendererID));
    GLCALL(glBufferData(GL_ARRAY_BUFFER, sizeof(renderer::Vertex) * 4, nullptr, GL_DYNAMIC_DRAW));

    // Coords
    GLCALL(glEnableVertexAttribArray(1));
    GLCALL(glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(renderer::Vertex), (const void*)offsetof(renderer::Vertex, Coords)));

    // Rgba
    // GLCALL(glEnableVertexAttribArray(2));
    // GLCALL(glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(renderer::Vertex), (const void*)offsetof(renderer::Vertex, Coords)));

    // TexCoords
    GLCALL(glEnableVertexAttribArray(2));
    GLCALL(glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(renderer::Vertex), (const void*)offsetof(renderer::Vertex, TexCoords)));

    // TextureIndex
    // GLCALL(glEnableVertexAttribArray(4));
    // GLCALL(glVertexAttribPointer(4, 1, GL_FLOAT, GL_FALSE, sizeof(renderer::Vertex), (const void*)offsetof(renderer::Vertex, Coords)));

    // Indices
    unsigned int indicies[] =
    {
        0, 1, 2, 2, 3, 0
    };

    unsigned int elementbuffer;
    GLCALL(glGenBuffers(1, &elementbuffer));
    GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer));
    GLCALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), indicies, GL_STATIC_DRAW));

    {
        bool print = true;

        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
        {
            /* Render here */
            renderer::Clear();

            // TODO change this
            renderer::Vertex vertecies2[4];

            // Vertecies
            std::pair<renderer::Vertex*, int> obj = renderer::ParseObjects(map, shader, vertecies2);
            renderer::Vertex* vertecies = obj.first;
            int verteciesSize = obj.second;

            // Prints the vertecies
            if (print)
            {
                std::cout << std::endl << "Render Data" << std::endl;

                for (int i = 0; i < verteciesSize; i++)
                {
                    // Coords
                    for (int j = 0; j < 2; j++)
                        std::cout << vertecies[i].Coords[j] << " ";
                    std::cout << " | ";

                    // TexCoords
                    for (int j = 0; j < 2; j++)
                        std::cout << vertecies[i].TexCoords[j] << " ";
                    std::cout << std::endl;
                }

                print = false;
            }

            // MVP
            glm::mat4 proj = glm::ortho(0.0f, 1920.0f, 0.0f, 1080.0f, -1.0f, 1.0f);
            glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
            glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));

            glm::mat4 mvp = proj;
            shader.SetUniformMat4f("u_MVP", mvp);

            // Write Buffer
            GLCALL(glBindBuffer(GL_ARRAY_BUFFER, rendererID));
            GLCALL(glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(renderer::Vertex) * 4, vertecies));

            GLCALL(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)0));

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
