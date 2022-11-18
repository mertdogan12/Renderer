#include "memory"
#include "iostream"

#include "Testing.h"
#include "renderer/Renderer.h"

namespace testing {
    Testing::Testing(const std::string& name, const float& width, const float& height) :
        width(width), height(height), name(name)
    {
        init();        
        start();
    }

    Testing::~Testing()
    {
        end();
    }

    void Testing::init()
    {
        /* GLFW */
        // Initialize the library
        if (!glfwInit())
            throw TestingExeption(name, "GLFW initialisation failed");

        // Create a windowed mode window and its OpenGL context
        window = glfwCreateWindow(width, height, "Renderer", NULL, NULL);
        if (!window)
        {
            throw TestingExeption(name, "GLFW window creation failed");
        }

        // GLFW hints
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        // Make the window's context current
        glfwMakeContextCurrent(window);

        glfwSwapInterval(1);

        /* Renderer */
        renderer::Init();

        /* Test */
        if (tests.find(name) == tests.end())
            throw TestingExeption(name, "The test with the given name does not exists");

        test.reset(tests[name].release());
    }

    void Testing::start()
    {
        test->init();

        while (!glfwWindowShouldClose(window))
        {
            /* Clear */
            renderer::Renderer::clear();

            /* Parses the map into vertecies and indicies */
            renderer::SizeStruct sizes = renderer::Renderer::calcCount();

            renderer::Vertex vertecies[sizes.Verticies];
            unsigned int indicies[sizes.Indices];
            renderer::Renderer::parseObjects(vertecies, indicies);

            /* Test */
            test->run();

            /* Draws */
            renderer::Draw(width, height, sizes, vertecies, indicies);

            /* Swap front and back buffers */
            glfwSwapBuffers(window);

            /* Poll for and process events */
            glfwPollEvents();
        }
    }

    void Testing::end()
    {
        glfwDestroyWindow(window);
        // glfwTerminate(true);
    }

    TestingExeption::TestingExeption(const std::string testName, 
            const std::string message) 
    {
        _message = "Test " + testName + " failed | " + message;
    };

    const char* TestingExeption::what() const throw ()
    {
        return _message.c_str();
    }
}
