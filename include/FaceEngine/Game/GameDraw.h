#ifndef FACEENGINE_GAME_GAMEDRAW_H_
#define FACEENGINE_GAME_GAMEDRAW_H_

#include <cstdint>

namespace FaceEngine
{
    class GameDraw
    {
        friend class Game;
    private:
        inline GameDraw() { }

        double lastDraw;
    public:
        inline const double LastDraw() const noexcept
        {
            return lastDraw;
        }
    };
}

#endif