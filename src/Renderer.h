#pragma once

#include "unordered_map"

#include "VertexObject.h"
#include "Shader.h"

#define ASSERT(x) if (!(x)) __builtin_trap();

// Clears all existing OpenGL error.
// Executest the given function and check for errors.
#define GLCALL(x) GLClearError();\
    x;\
    ASSERT(GLLogCall(#x, __FILE__, __LINE__))

void GLClearError();
bool GLLogCall(const char* function, const char* file, int line);

namespace renderer {
    std::pair<Vertex*, int> ParseObjects(std::unordered_map<std::string, VertexObject> &objects, Shader &shader, Vertex* vertecies);
    void Clear();
};
