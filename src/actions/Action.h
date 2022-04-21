#pragma once

namespace actions {
    // Time in frames
    struct Time {
        int start;
        int end;
        float speed;
    };

    class Action
    {
        public:
            Action(const char& txtId, const int& start, const int& end);
            const char textureId;
            Time time;
            virtual void run();
    };
}
