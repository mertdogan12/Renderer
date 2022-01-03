#pragma once

#define ASSERT(x) if (!(x)) __builtin_trap();

// Clears all existing OpenGL error.
// Executest the given function and check for errors.
#define GLCALL(x) GLClearError();\
    x;\
    ASSERT(GLLogCall(#x, __FILE__, __LINE__))

void GLClearError();
bool GLLogCall(const char* function, const char* file, int line);

namespace renderer {
    class Renderer
    {
        public:
            void Clear() const;
    };
};
