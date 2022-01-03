#include "GL/glew.h"
#include "iostream"

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
    void Renderer::Clear() const 
    {
        GLCALL(glClear(GL_COLOR_BUFFER_BIT));
    }
}
