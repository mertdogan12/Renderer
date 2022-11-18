#pragma once

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
        std::unordered_map<std::string, std::unique_ptr<Test>> tests = {
            { "coords", std::unique_ptr<Test>(new CoordsTest()) }
        };

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
