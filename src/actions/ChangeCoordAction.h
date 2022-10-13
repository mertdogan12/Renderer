#pragma once

#include "actions/Action.h"

namespace actions {
    class ChangeCoordsAction: public Action
    {
        // How much x or y should be increased
        struct Speed {
            int x;
            int y;
        };

        struct Position {
            float x;
            float y;
            float scaleX;
            float scaleY;
        };

        public:
            ChangeCoordsAction(Time time, char textureId);
            void init(const char *args) override;
            void run() override;

        private:
            Speed speed;

            // end coordinates
            Position endPos;
    };
}
