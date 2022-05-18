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
        bool fullscreen;
        bool vsync;
    public:
        inline const std::string& GetTitle() const noexcept
        {
            return title;
        }

        void SetTitle(const std::string&) noexcept;
        
        inline const Resolution& GetResolution() const noexcept
        {
            return currentRes;
        }

        inline const bool GetVsync() const noexcept
        {
            return vsync;
        }

        void SetResolution(const Resolution&);

        void SetVSync(const bool) noexcept;

        void Clear() const noexcept;
    };
}

#endif