#include "actions/ChangeCoordAction.h"

#include "data/Helper.h"
#include "renderer/Renderer.h"
#include "renderer/VertexObject.h"

namespace actions {
    ChangeCoordsAction::ChangeCoordsAction(Time time, char textureId) 
        : Action(time, textureId) {}

    void ChangeCoordsAction::init(const char *args)
    {
        // Parses the args
        endPos.x = data::charsToFloat(args);
        endPos.y = data::charsToFloat(args, 4 * 1);
        endPos.scaleX = data::charsToFloat(args, 4 * 2);
        endPos.scaleY = data::charsToFloat(args, 4 * 3);

        // Gets the current Position from the Texture and sets it to the start Position
        renderer::VertexObject* obj = renderer::Renderer::map[0];

        Position startPos = 
        {
            obj->posX, 
            obj->posY, 
            obj->posScaleX, 
            obj->posScaleY
        };

        // Calcuates the speed
        speed.x = (endPos.x - startPos.x) / (time.end - time.currentPos);
        speed.y = (endPos.y - startPos.y) / (time.end - time.currentPos);
    }

    void ChangeCoordsAction::run() 
    {

    }
}
