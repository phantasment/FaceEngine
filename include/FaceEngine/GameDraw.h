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

        double delta;
        std::uint32_t fps;
    public:
        /**
         * @brief Returns the number of seconds that have passed since the last draw. If your game is running at 60 frames per second the delta will be ~0.016.
         * 
         * @return double 
         */
        inline double GetDelta() const noexcept
        {
            return delta;
        }

        inline double GetFPS() const noexcept
        {
            return fps;
        }
    };
}

#endif