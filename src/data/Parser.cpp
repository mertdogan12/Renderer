#include "Parser.h"

#include "iostream"

#include "renderer/Renderer.h"
#include "Helper.h"

namespace data {
    Parser::Parser(const std::string &inp)
    {
        int txtSize = parseTextures(inp, 0);
        parseActions(inp, txtSize);
    }

    int Parser::parseTextures(const std::string &inp, const int &start)
    {
        int offset = start;

        char id = inp[offset];
        offset++;

        float x = charsToInt(inp.substr(offset, 4).c_str());
        float y = charsToInt(inp.substr(offset + 4, 4).c_str());
        float scaleX = charsToInt(inp.substr(offset + 4 * 2, 4).c_str());
        float scaleY = charsToInt(inp.substr(offset + 4 * 3, 4).c_str());
        offset += 4 * 4;

        char pathLen = inp[offset];
        std::string path = inp.substr(offset + 1, pathLen);
        offset += 1 + pathLen;

        renderer::Renderer::map.insert({id, new renderer::VertexObject(x, y, scaleX, scaleY, path)});

        std::cout << "Texture loaded: " << (int) id << ", " << path << std::endl;

        if (inp[offset] == 0x0b)
            return offset;

        return parseTextures(inp, offset);
    }

    void Parser::parseActions(const std::string &inp, const int &start)
    {
        int offset = start + 1;
        char textureId = inp[offset];
        char actionId = inp[offset + 1];

        // Check if texture exists
        if ( renderer::Renderer::map.find(textureId) == renderer::Renderer::map.end())
            throw  std::runtime_error(std::string("Texture does not exists: ").append(&textureId));
        offset += 2;

        int _start = charsToInt(inp.substr(offset, 4).c_str());
        int _end = charsToInt(inp.substr(offset + 4, 4).c_str());

        std::cout << _end << std::endl;
    }
}
