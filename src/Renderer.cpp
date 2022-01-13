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
    // Just runs glClear
    void Clear()
    {
        GLCALL(glClear(GL_COLOR_BUFFER_BIT));
    }

    // Make of all VertexObjects one array with all the vertecies.
    // Also create the indicies based on the vertecies.
    // Binds the Texture to the correct spot and set the Uniform.
    // Returns then the vertecies and the indicies.
    std::pair<Vertex*, int> ParseObjects(std::unordered_map<std::string, VertexObject> &objects, Shader &shader, Vertex* vertecies)
    {
        // int size = objects.size() * 4;
        // Vertex vertecies[size];
        int size = 4;

        unsigned int textSlot = 0;
        for (std::pair<std::string, VertexObject> obj: objects)
        {
            VertexObject object = obj.second;

            // Vertecies
            std::memcpy(vertecies, object.Vertexs, sizeof(Vertex) * 4);

            // Texture
            object.BindTexture(textSlot);
            shader.SetUniform1i("u_Texture", textSlot);
        }

        return { vertecies, size };
    }
}
