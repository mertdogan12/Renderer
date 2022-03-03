#include "VertexObject.h"

#include "glm/glm.hpp"

#include "iostream"

namespace renderer {
    // Object with the with all his Vertecis and the corresponding Texture object
    // vec2 Coordinates
    // vec4 Color
    // vec2 Texture Coordinates
    // float Texture Index
    VertexObject::VertexObject(const std::string name, const float coords[2], 
            const float scaleX, const float scaleY, const std::string& texturePath)
        : Name(name), 
          VertexTexture(texturePath), 
          posX(coords[0]), 
          posY(coords[1]), 
          posScaleX(scaleX),
          posScaleY(scaleY)
    {
        const float width = scaleX * VertexTexture.GetWidth();
        const float height = scaleY * VertexTexture.GetHeight();

        Vertex v0 = 
        {
            glm::vec2(coords[0], coords[1]),
            glm::vec4(0.0f, 0.0f, 0.0f, 0.0f),
            glm::vec2(0.0f, 0.0f),
            0.0f
        };

        Vertex v1 = 
        {
            glm::vec2(coords[0] + width, coords[1]),
            glm::vec4(0.0f, 0.0f, 0.0f, 0.0f),
            glm::vec2(1.0f, 0.0f),
            0.0f
        };

        Vertex v2 = 
        {
            glm::vec2(coords[0] + width, coords[1] + height),
            glm::vec4(0.0f, 0.0f, 0.0f, 0.0f),
            glm::vec2(1.0f, 1.0f),
            0.0f
        };

        Vertex v3 = 
        {
            glm::vec2(coords[0], coords[1] + height),
            glm::vec4(0.0f, 0.0f, 0.0f, 0.0f),
            glm::vec2(0.0f, 1.0f),
            0.0f
        };

        Vertexs[0] = v0;
        Vertexs[1] = v1;
        Vertexs[2] = v2;
        Vertexs[3] = v3;
    }

    // Change the Coordinates and the scale of the Object.
    // Also every variable is optional.
    void VertexObject::ChangeCoords(float x, float y, float scaleX, float scaleY)
    {
        std::cout << posX << " | " << posY << std::endl;
        std::cout << scaleX << " | " << scaleY << std::endl;

        // Looks if the variables are defined (not -1). 
        // If not it defined them with the previouse value. 
        // Then it update the positon of the Object. 
        x = (x != -1.0f) ? x : posX;
        y = (y != -1.0f) ? y : posY;
        scaleX = (scaleX != -1.0f) ? scaleX : posScaleX;
        scaleY = (scaleY != -1.0f) ? scaleY : posScaleY;

        const float width = scaleX * VertexTexture.GetWidth();
        const float height = scaleY * VertexTexture.GetHeight();

        Vertexs[0].Coords = glm::vec2(x, y);
        Vertexs[1].Coords = glm::vec2(x + width, y);
        Vertexs[2].Coords = glm::vec2(x + width, y + height);
        Vertexs[3].Coords = glm::vec2(x, y + height);

        posX = x;
        posY = y;
        posScaleX = scaleX;
        posScaleY = scaleY;
    }

    // Binds the Texture and sets the Texture index
    void VertexObject::BindTexture(unsigned int slot)
    {
        setTextureIndex((float) slot);
        VertexTexture.Bind(slot);
    }

    void VertexObject::setTextureIndex(float index)
    {
        for (int i = 0; i < 4; i++)
            Vertexs[i].TextureIndex = index;
    }
}
