#include "GL/glew.h"
#include "iostream"
#include "unordered_map"
#include "cstring"

#include "Renderer.h"

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
    // Returns then an pointer to the array and the size of the array.
    // first: Vertex poitner, second: size
    std::pair<Vertex*, int> ParseObjects(std::unordered_map<std::string, VertexObject> objects)
    {
        int size = objects.size() * 4;
        Vertex vertecies[size];

        for (std::pair<std::string, VertexObject> obj: objects)
        {
            VertexObject object = obj.second;
            std::memcpy(vertecies, object.Vertexs, sizeof(Vertex) * 4);
        }

        return { vertecies, size };
    }
}
