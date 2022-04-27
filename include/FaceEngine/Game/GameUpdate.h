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
        std::uint32_t ups;
    public:
        /**
         * @brief Returns the number of seconds that have passed since the last update. If your game is running at 60 frames per second the delta will be ~0.016.
         * 
         * @return double
         */
        inline double Delta() const noexcept
        {
            return delta;
        }

        inline double UPS() const noexcept
        {
            return ups;
        }
    };
}

#endif