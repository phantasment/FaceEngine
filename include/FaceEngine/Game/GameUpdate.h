#ifndef FACEENGINE_GAME_GAMEUPDATE_H_
#define FACEENGINE_GAME_GAMEUPDATE_H_

#include <cstdint>

namespace FaceEngine
{
    class GameUpdate
    {
        friend class Game;
    private:
        inline GameUpdate() { }

        double delta;
    public:
        // Returns the number of seconds that have passed since the last update.
        // If your game is running at 60 frames per second the delta will be ~0.016.
        inline const double Delta() const noexcept
        {
            return delta;
        }
    };
}

#endif