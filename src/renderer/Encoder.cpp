#include "Encoder.h"

#include "iostream"
#include "string"

namespace renderer
{
    Encoder::Encoder(const std::string filePath, const unsigned int width, const unsigned int height)
    {
        std::string size = std::to_string(width) + "x" + std::to_string(height);

        popen
            (
                std::string
                (
                    "ffmpeg \
                    -y \
                    -f rawvideo \
                    -vcodec rawvideo \
                    -s " + size + " \
                    -pix_fmt rgb24 \
                    -r 60 \
                    -i pipe:0 \
                    -an \
                    -vf vflip \
                    -c:v libx265 \
                    -color_range 1 \
                    -colorspace 1 \
                    -color_trc 1 \
                    -color_primaries 1 \
                    -movflags +write_colr \
                    out.mp4"
                 ).c_str(),
                 "w"
            );

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
