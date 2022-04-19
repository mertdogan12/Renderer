#include "Encoder.h"

#include "iostream"
#include "string"

namespace renderer
{
    Encoder::Encoder(const std::string filePath, const unsigned int width, const unsigned int height)
        : ffmpeg(popen(std::string("ffmpeg -vcodec rawvideo -f rawvideo -pix_fmt rgb24 \
                        -s " + std::to_string(width) + "x" + std::to_string(height) +
                        " -i pipe:0 -vf vflip -vcodec h264 -r 60 " + filePath).c_str(), "w"))
    {
        if (!ffmpeg)
        {
            throw "Ffmpeg command failed";
        }
    }

    void Encoder::Write(GLbyte* data, int size)
    {
        fwrite(data, size, 1, ffmpeg);
    }
}
