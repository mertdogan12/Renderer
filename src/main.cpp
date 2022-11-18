#define GLEW_STATIC
#include "GL/glew.h"
#include "GLFW/glfw3.h"


#include "iostream"
#include "fstream"
#include "unordered_map"
#include "cstring" 
#include "string" 
#include "chrono"
#include "thread"
#include "memory"

#include "renderer/Renderer.h"
#include "renderer/Shader.h"
#include "renderer/VertexObject.h"
#include "renderer/Encoder.h"

#include "testing/Testing.h"

int main() 
{ 
    const float width = 1920.0f, height = 1080.0f;

    std::unique_ptr<testing::Testing> testing;

    try
    {
        testing.reset(new testing::Testing("coords", width, height));
    } catch (testing::TestingExeption e)
    {
        std::cout << e.what() << std::endl; 
        return -1;
    }

    return 0;
} 
