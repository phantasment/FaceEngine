#ifndef FACEENGINE_GAMEUPDATE_H_
#define FACEENGINE_GAMEUPDATE_H_

#include <cstdint>
#include <vector>

#include "FaceEngine/OGL.h"
#include "FaceEngine/Math/Vector2.h"
#include "FaceEngine/Exception.h"

namespace FaceEngine
{
    struct TypedKey
    {
        int Key;
        bool Shift;
        bool Control;
        bool Alt;
        bool CapsLock;
    };

    class GameUpdate
    {
        friend class Game;
    private:
        GLFWwindow* winHandle;
        double delta;
        std::uint32_t ups;

        int* previousKeys;
        int* currentKeys;
        int* previousMice;
        int* currentMice;
        Vector2f mousePos;
        std::vector<TypedKey> keysTyped;

        static GameUpdate* thisptr;
        static void KeyCallback(GLFWwindow*, int, int, int, int);
        static void MouseCallback(GLFWwindow*, int, int, int);
        static void CursorPosCallback(GLFWwindow*, double, double);

        GameUpdate(GLFWwindow* gw) noexcept;
        ~GameUpdate() noexcept;

        void UpdateInput() noexcept;
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

        bool IsKeyDown(int) const;
        bool IsKeyPressed(int) const;
        bool IsMouseDown(int) const;
        bool IsMousePressed(int) const;
        bool IsMouseReleased(int) const;

        inline const Vector2f& GetCursorPos() const noexcept { return mousePos; }

        inline const std::vector<TypedKey>& GetKeysTyped() const noexcept { return keysTyped; }
    };
}

#endif