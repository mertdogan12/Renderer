#pragma once

#include "Texture.h"

#include "string"
#include "memory"

#include "glm/glm.hpp"

namespace renderer {
    struct Vertex 
    {
        glm::vec2 Coords;
        glm::vec4 Rgba;
        glm::vec2 TexCoords;
        float TextureIndex;
    };

    class VertexObject
    {
        public:
            VertexObject(const std::string name, const float coords[2], 
                    const float scaleX, const float scaleY, const std::string& texturePath);

            std::string Name;
            Vertex Vertexs[4];

            Texture VertexTexture;
            void BindTexture(unsigned int slot = 0);
            void ChangeCoords(const float x = posX, const float y = posY, const float scaleX = posScaleX, const float scaleY = posScaleY);

        private:
            void setTextureIndex(float index);
            static float posX, posY;
            static float posScaleX, posScaleY;
    };
}
