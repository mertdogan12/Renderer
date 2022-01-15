#pragma once

#include "unordered_map"
#include "array"
#include "memory"

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
    struct SizeStruct
    {
        // First Array pointer, second size
        int Verticies;
        int Indices;
    };

    void Init();

    class Renderer 
    {
        public:
            static std::unordered_map<std::string, renderer::VertexObject> map;
            static Shader *shader;

            static void Clear();
            static void ParseObjects(Vertex* vertecies, unsigned int* indicies);
            static SizeStruct CalcCount();
    };
};
