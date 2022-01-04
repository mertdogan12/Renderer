#include "VertexObject.h"

#include "glm/glm.hpp"

namespace renderer {
    VertexObject::VertexObject(const std::string name, const float coords[2], 
            const float width, const float height, const std::string& texturePath)
        : Name(name), VertexTexture(texturePath)
    {
        Vertex v0 = 
        {
            glm::vec3(coords[0], coords[1], 0.0f),
            glm::vec4(0.0f, 0.0f, 0.0f, 1.0f),
            glm::vec2(0.0f, 0.0f),
            0.0f
        };

        Vertex v1 = 
        {
            glm::vec3(coords[0] + width, coords[1], 0.0f),
            glm::vec4(0.0f, 0.0f, 0.0f, 1.0f),
            glm::vec2(1.0f, 0.0f),
            0.0f
        };

        Vertex v2 = 
        {
            glm::vec3(coords[0] + width, coords[1] + height, 0.0f),
            glm::vec4(0.0f, 0.0f, 0.0f, 1.0f),
            glm::vec2(1.0f, 1.0f),
            0.0f
        };

        Vertex v3 = 
        {
            glm::vec3(coords[0], coords[1] + height, 0.0f),
            glm::vec4(0.0f, 0.0f, 0.0f, 1.0f),
            glm::vec2(0.0f, 1.0f),
            0.0f
        };

        Vertexs[0] = &v0;
        Vertexs[1] = &v1;
        Vertexs[2] = &v2;
        Vertexs[2] = &v3;
    }

    // Binds the Texture and sets the Texture index
    void VertexObject::BindTexture(unsigned int slot)
    {
        setTextureIndex((float) slot);
        VertexTexture.Bind(slot);
    }

    void VertexObject::setTextureIndex(float index) const
    {
        for (int i = 0; i < 4; i++)
            Vertexs[i]->TextureIndex = index;
    }
}
