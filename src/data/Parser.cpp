#include "Parser.h"

#include "iostream"

#include "renderer/Renderer.h"
#include "data/Helper.h"
#include "actions/Action.h"
#include "actions/ChangeCoordAction.h"

namespace data {
    Parser::Parser(const std::string &inp)
    {
        int txtSize = parseTextures(inp, 0);
        parseActions(inp, txtSize + 1);
    }

    int Parser::parseTextures(const std::string &inp, const int &start)
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

        std::cout << "Texture loaded: " << (int) id << ", " << path 
            << ", " << x << ", " << y << std::endl;

        if (inp[offset] == 0x0b)
            return offset;

        return parseTextures(inp, offset);
    }

    void Parser::parseActions(const std::string &inp, const int &start)
    {
        int offset = start;
        char textureId = inp[offset];
        char actionId = inp[offset + 1];
        offset += 2;

        // Check if texture exists
        if ( renderer::Renderer::map.find(textureId) == renderer::Renderer::map.end())
            throw  std::runtime_error(std::string("Texture does not exists: ")
                    .append(std::to_string(int(textureId))));

        int _start = charsToInt(inp.substr(offset, 4).c_str());
        int _end = charsToInt(inp.substr(offset + 4, 4).c_str());
        offset += 4 * 2;

        std::unique_ptr<actions::Action> action;

        switch(int(actionId))
        {
            case 0:
                action.reset(new actions::ChangeCoordsAction(actions::Time{_start, _end, 0}
                            , textureId));

                // TODO Get byte array slice with the args
                action->init(inp.substr(offset, offset + 15).c_str());

                offset += 16;
                break;

            case 1:
                offset += 8;
                break;

            default:
                throw std::runtime_error(std::string("Action does not exists: ")
                        .append(std::to_string(int(actionId))));
        }

        std::cout << "--- Action parsed ---" << std::endl;
        std::cout << "Action id: " << int(actionId) << std::endl;
        std::cout << "Texture id: " << std::hex << int(textureId) << std::endl;

        if (inp[offset] == 0x0b)
            return;

        parseActions(inp, offset);
    }
}
