#pragma once

#include "string"
#include "GL/glew.h"

namespace renderer 
{
    class Encoder 
    {
        public: 
            Encoder(std::string filePath, const unsigned int width, const unsigned int height);
            void Write(GLbyte* data, int size);

        private:
           FILE* ffmpeg; 
    };
}
