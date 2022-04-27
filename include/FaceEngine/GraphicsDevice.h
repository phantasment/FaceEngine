#ifndef FACEENGINE_GRAPHICSDEVICE_H_
#define FACEENGINE_GRAPHICSDEVICE_H_

#include <vector>

#include "FaceEngine/OGL.h"
#include "FaceEngine/Display.h"

namespace FaceEngine
{
    class GraphicsDevice
    {
        friend class Game;
    private:
        GraphicsDevice();

        std::vector<Display> displays;
    public:
        inline const std::vector<Display>& Displays() const noexcept
        {
            return displays;
        }

        inline const Display& PrimaryDisplay() const noexcept
        {
            return displays[0];
        }
    };
}

#endif