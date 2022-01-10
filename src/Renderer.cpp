#include "GL/glew.h"
#include "iostream"
#include "unordered_map"
#include "cstring"

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
    bool log = false;

    // Just runs glClear
    void Clear()
    {
        GLCALL(glClear(GL_COLOR_BUFFER_BIT));
    }

    // Make of all VertexObjects one array with all the vertecies.
    // Binds the Texture to the correct spot and set the Uniform.
    // Returns then an pointer to the array and the size of the array.
    // first: Vertex poitner, second: size
    std::pair<Vertex*, int> ParseObjects(std::unordered_map<std::string, VertexObject> &objects, Shader &shader, Vertex* vertecies)
    {
        // int size = objects.size() * 4;
        // Vertex vertecies[size];
        int size = 4;

        int textSlot = 0;
        for (std::pair<std::string, VertexObject> obj: objects)
        {
            VertexObject object = obj.second;

            // Log
            if (!log)
            {
                std::cout << "Parse Objects" << std::endl;
                
                for (int i = 0; i < 4; i++)
                {
                    // Coords
                    for (int j = 0; j < 3; j++)
                    {
                        std::cout << object.Vertexs[i].Coords[j] << " ";
                    }
                    std::cout << " | ";

                    // TexCoords
                    for (int j = 0; j < 2; j++)
                    {
                        std::cout << object.Vertexs[i].TexCoords[j] << " ";
                    }
                    std::cout << std::endl;
                }
            }

            // Vertecies
            std::memcpy(vertecies, object.Vertexs, sizeof(Vertex) * 4);

            // Texure
            object.BindTexture(textSlot);
            shader.SetUniform1i("u_Texture", textSlot);
        }

        // Prints the vertecies
        if (!log)
        {
            std::cout << std::endl << "Render Data" << std::endl;

            for (int i = 0; i < size; i++)
            {
                // Coords
                for (int j = 0; j < 3; j++)
                    std::cout << vertecies[i].Coords[j] << " ";
                std::cout << " | ";

                // TexCoords
                for (int j = 0; j < 2; j++)
                    std::cout << vertecies[i].TexCoords[j] << " ";
                std::cout << std::endl;
            }

            log = true;
        }

        return { vertecies, size };
    }
}
