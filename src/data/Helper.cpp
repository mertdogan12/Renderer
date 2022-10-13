#include "Helper.h"

#include "cstring"

namespace data {
    float charsToFloat(const char* inp)
    {
        float out;
        std::memcpy(&out, inp, 4);

        return out;
    }

    float charsToFloat(const char* inp, int offset)
    {
        return charsToFloat(&inp[offset]);
    }

    int charsToInt(const char* inp)
    {
        int out;
        std::memcpy(&out, inp, 4);

        return out;
    }
}
