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

int main(int argc, char* argv[]) 
{ 
    if (argc != 2)
    {
        std::cout << "You need to give the name of the test | renderer <name of the test>" << std::endl;
        return -1;
    }

    std::string name = argv[1];

    const float width = 1920.0f, height = 1080.0f;

    std::unique_ptr<testing::Testing> testing;

    try
    {
        testing.reset(new testing::Testing(name, width, height));
    } catch (testing::TestingExeption e)
    {
        std::cout << e.what() << std::endl; 
        return -1;
    }

    return 0;
} 
