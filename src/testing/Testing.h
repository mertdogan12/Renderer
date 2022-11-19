#pragma once
#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include "string"
#include "unordered_map"
#include "memory"
#include "exception"

#include "Test.h"
#include "CoordsTest.h"

namespace testing {
    class Testing
    {
    public:
        Testing(const std::string& name, const float& width, const float& height);
        ~Testing();

        GLFWwindow* window;

    private:
        // name of a test --> test ptr
        std::unordered_map<std::string, std::unique_ptr<Test>> tests;

        std::unique_ptr<Test> test;

        const float width, height;
        const std::string name;

        void init();
        void start();
        void end();
    };

    struct TestingExeption : public std::exception
    {
        TestingExeption(const std::string testName, const std::string message);
        const char* what() const throw ();

    private:
        std::string _message;
    };
}
