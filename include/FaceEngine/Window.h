#ifndef FACEENGINE_WINDOW_H_
#define FACEENGINE_WINDOW_H_

#include <string>

#include "FaceEngine/OGL.h"
#include "FaceEngine/Exception.h"
#include "FaceEngine/GraphicsDevice.h"

namespace FaceEngine
{
    class Window
    {
        friend class Game;
    private:
        Window(GraphicsDevice*);
        GraphicsDevice* graphicsDevice;
        GLFWwindow* winHandle;
        std::string title;
        Resolution currentRes;
        bool vsync;
    public:
        inline const std::string& Title() const noexcept
        {
            return title;
        }

        void SetTitle(const std::string&) noexcept;
        
        inline const Resolution& CurrentResolution() const noexcept
        {
            return currentRes;
        }

        inline const bool IsVsync() const noexcept
        {
            return vsync;
        }

        void SetVSync(const bool) noexcept;
    };
}

#endif