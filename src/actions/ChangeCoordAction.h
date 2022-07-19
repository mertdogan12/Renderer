#pragma once

#include "Action.h"

namespace actions {
    class ChangeCoordsAction: public Action
    {
        public:
            ChangeCoordsAction();
            void run();
            void test();
    };
}
