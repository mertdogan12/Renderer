#include "Parser.h"

#include "iostream"

#include "renderer/Renderer.h"
#include "Helper.h"

namespace data {
    Parser::Parser(const std::string &inp)
    {
        parseTextures(inp, 0);
    }

    void Parser::parseTextures(const std::string &inp, const int start)
    {
        int offset = start;

        char id = inp[offset];
        offset++;

        float x = charsToFloat(inp.substr(offset, 4).c_str());
        float y = charsToFloat(inp.substr(offset + 4, 4).c_str());
        float scaleX = charsToFloat(inp.substr(offset + 4 * 2, 4).c_str());
        float scaleY = charsToFloat(inp.substr(offset + 4 * 3, 4).c_str());
        offset += 4 * 4;

        char pathLen = inp[offset];
        std::string path = inp.substr(offset + 1, pathLen);
        offset += 1 + pathLen;

        renderer::Renderer::map.insert({id, new renderer::VertexObject(x, y, scaleX, scaleY, path)});

        std::cout << "Texture loaded: " << (int) id << ", " << path << std::endl;

        if (inp[offset] == 0x0b)
            return;

        parseTextures(inp, offset);
    }
}
