#pragma once

#include "Action.h"

namespace actions {
    class ChangeCoordsAction: public Action
    {
        public:
            void init(char *args) override;
            void run() override;
    };
}
