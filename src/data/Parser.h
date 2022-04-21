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
            // Returns the size of the textures
            int parseTextures(const std::string &inp, const int &start);

            // Parses the Actions from the inp.
            // Then creates and linkedlist with all the acitons in the right order.
            void parseActions(const std::string &inp, const int &start);
    };
}
