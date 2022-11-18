#pragma once

namespace testing {
    class Test
    {
    public:
        virtual void init() = 0;
        virtual void run() = 0;
        virtual void end() = 0;
    };
}
