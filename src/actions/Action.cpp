#include "actions/Action.h"

namespace actions {
    Action::Action(Time time, char textureId) : time (time), textureId(textureId) {}

    void Action::run() {}
    void Action::init(char *args) {}
}
