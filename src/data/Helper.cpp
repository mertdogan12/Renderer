#include "Helper.h"

#include "cstring"

namespace data {
    float charsToFloat(const char* inp)
    {
        float out;
        std::memcpy(&out, inp, 4);

        return out;
    }
}
