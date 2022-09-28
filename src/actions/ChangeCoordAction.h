#pragma once

#include "actions/Action.h"

namespace actions {
    class ChangeCoordsAction: public Action
    {
        public:
            ChangeCoordsAction(Time time, char textureId);
            void init(char *args) override;
            void run() override;
    };
}
