#pragma once

#include "Test.h"

#include "memory"

#include "renderer/Renderer.h"

namespace testing {
    class CoordsTest : public Test
    {
    public:
        void init() override;
        void run() override;
        void end() override;

    private:
        const char picture = 0x00;
        float x = 0.0f, y = 0.0f;
    };
}
