#pragma once

#include "string"

namespace data {
    class Parser
    {
        public:
            Parser(const std::string &inp);

        private:
            // Parses the Textures from the inp.
            // Then creates the parsed textures
            void parseTextures(const std::string &inp, const int start);
    };
}
