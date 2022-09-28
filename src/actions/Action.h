#pragma once

#include "array"

namespace actions {
    // Time in frames
    struct Time {
        int currentPos;
        int end;
        float speed;
    };

    class Action
    {
        public:
            Action(Time time, char textureId);
            const char textureId;
            virtual void run();
            virtual void init(char* args);

        private:
            Time time;
    };
}
