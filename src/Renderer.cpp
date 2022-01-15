#include "GL/glew.h"
#include "iostream"
#include "unordered_map"
#include "cstring"
#include "memory"

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

    void Init()
    {
        // Shader
        Renderer::shader = new Shader("res/shaders/Basic.shader");
        renderer::Renderer::shader->Bind();
    }

    // Just runs glClear
    void Renderer::Clear()
    {
        GLCALL(glClear(GL_COLOR_BUFFER_BIT));
    }

    bool print = true;

    // Also create the indicies based on the vertecies.
    // Binds the Texture to the correct spot and set the Uniform.
    // Returns then the vertecies and the indicies.
    // First vertecies, second indicies
    void Renderer::ParseObjects(Vertex* vertecies, unsigned int* indicies)
    {
        unsigned int textSlot = 0;
        unsigned int index = 0;
        for (std::pair<std::string, VertexObject> obj: map)
        {
            VertexObject object = obj.second;

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

            // Texture
            object.BindTexture(textSlot);
            shader->SetUniform1i("u_Texture", textSlot);

            index++;
        }
    }

    // Claculate the count of the vertecies and the indicies
    // First vertecies, Second indicies
    SizeStruct Renderer::CalcCount()
    {
        return { (int) map.size() * 4, (int) map.size() * 6 };
    }
}
