#include "GL/glew.h"
#include "iostream"
#include "unordered_map"
#include "cstring"
#include "memory"
#include "exception"

#include "Renderer.h"
#include "Shader.h"

// Just removes all GL errors
void GLClearError()
{
    while (glGetError() != GL_NO_ERROR);
}

// Prints an existing OpenGL errors with the giving function name, the file and the line.
// If no error exist if just return false (else it return true);
bool GLLogCall(const char* function, const char* file, int line)
{
    while(GLenum error = glGetError())
    {
        std::cout << "[OpenGL Error] (" << error << "): " << function << " " << file << ":" << line << std::endl;
        return false;
    }
    
    return true;
}


namespace renderer {
    std::unordered_map<std::string, renderer::VertexObject> Renderer::map;
    Shader *Renderer::shader = nullptr;
    unsigned int *Renderer::vertexArray = nullptr;
    unsigned int *Renderer::indicies = nullptr;

    void Init()
    {
        /* GLEW */
        GLenum err = glewInit();
        if (err != GLEW_OK)
            throw std::runtime_error("Glfw Error");

        std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;

        /* Vertex Array */
        unsigned int test; 
        GLCALL(glGenBuffers(1, Renderer::vertexArray));
        GLCALL(glBindBuffer(GL_ARRAY_BUFFER, *Renderer::vertexArray));
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

        /* Indicies */
        unsigned int test1;
        GLCALL(glGenBuffers(1, Renderer::indicies));
        GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *Renderer::indicies));
        GLCALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * 1000, nullptr, GL_DYNAMIC_DRAW));

        /* Shader */
        Renderer::shader = new Shader("res/shaders/Basic.shader");
        renderer::Renderer::shader->Bind();

        /* Blending */
        GLCALL(glEnable(GL_BLEND));
        GLCALL(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
    }

    // Just runs glClear
    void Renderer::clear()
    {
        GLCALL(glClear(GL_COLOR_BUFFER_BIT));
    }

    bool print = true;

    // Also create the indicies based on the vertecies.
    // Binds the Texture to the correct spot and set the Uniform.
    // Returns then the vertecies and the indicies.
    // First vertecies, second indicies
    void Renderer::parseObjects(Vertex* vertecies, unsigned int* indicies)
    {
        int textures[32];
        unsigned int index = 0;
        for (std::pair<std::string, VertexObject> obj: map)
        {
            VertexObject object = obj.second;

            // Texture
            object.BindTexture(index);
            textures[index] = index;

            // Vertecies
            std::memcpy(&vertecies[index * 4], object.Vertexs, sizeof(Vertex) * 4);

            // Indices
            unsigned int indiciesValue[6] = 
            {
                0 + 4 * index,
                1 + 4 * index,
                2 + 4 * index,
                2 + 4 * index,
                3 + 4 * index,
                0 + 4 * index
            };
            std::memcpy(&indicies[index * 6], indiciesValue, sizeof(unsigned int) * 6);

            index++;
        }

        shader->SetUniform1iv("u_Textures", textures);
    }

    // Claculate the count of the vertecies and the indicies
    // First vertecies, Second indicies
    SizeStruct Renderer::calcCount()
    {
        return { (int) map.size() * 4, (int) map.size() * 6 };
    }
}
