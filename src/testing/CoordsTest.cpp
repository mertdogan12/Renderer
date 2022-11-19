#include "CoordsTest.h"

#include "renderer/Renderer.h"

namespace testing {
    void CoordsTest::init()
    {
        renderer::VertexObject* obj = new renderer::VertexObject(x, y, 1.0f, 1.0f, "res/textures/test571x840.jpg");
        renderer::Renderer::map.insert({picture, obj});
    };

    void CoordsTest::run()
    {
        renderer::Renderer::map[picture]->ChangeCoords(x, y);

        if (x > 1000)
        {
            x = 0;
            y = 0;
        }

        x++;
        y++;
    };

    void CoordsTest::end()
    {
        delete renderer::Renderer::map[picture];
    };
}
