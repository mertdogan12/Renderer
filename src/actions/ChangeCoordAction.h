#pragma once

#include "actions/Action.h"

namespace actions {
    class ChangeCoordsAction: public Action
    {
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
            Position speed;

            // end coordinates
            Position endPos;
    };
}
