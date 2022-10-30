#include "Encoder.h"

#include "iostream"
#include "string"

namespace renderer
{
    Encoder::Encoder(const std::string filePath, const unsigned int width, const unsigned int height)
        : ffmpeg(popen(std::string("ffmpeg -f rawvideo -pix_fmt rgb24 \
                        -r 60 -s " + std::to_string(width) + "x" + std::to_string(height) +
                        " -i pipe:0 -vf vflip libx265 " + filePath).c_str(), "w"))
    {
        if (!ffmpeg)
        {
            throw "Ffmpeg command failed";
        }
    }

    Encoder::~Encoder()
    {
        pclose(ffmpeg);
    }

    void Encoder::Write(GLbyte* data, int size)
    {
        fwrite(data, size, 1, ffmpeg);
    }
}
