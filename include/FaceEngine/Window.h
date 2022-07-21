#ifndef FACEENGINE_WINDOW_H_
#define FACEENGINE_WINDOW_H_

#include <string>

#include "FaceEngine/Resource.h"
#include "FaceEngine/OGL.h"
#include "FaceEngine/Exception.h"
#include "FaceEngine/GraphicsDevice.h"
#include "FaceEngine/Graphics/Colour.h"

namespace FaceEngine
{
    class Window : public Resource
    {
        friend class Game;
    private:
        Window(GraphicsDevice*);
        GraphicsDevice* graphicsDevice;
        GLFWwindow* winHandle;
        std::string title;
        Resolution resolution;
        bool fullscreen;
        bool vsync;

        Colour clearColour;
    public:
        inline bool IsDisposed() noexcept override { return winHandle == nullptr; }

        void Dispose() noexcept override;

        inline const std::string& GetTitle() const noexcept { return title; }
        void SetTitle(const std::string&) noexcept;
        
        inline const Resolution& GetResolution() const noexcept
        {
            if (fullscreen)
            {
                return graphicsDevice->GetPrimaryDisplay().GetMaxResolution();
            }
            else
            {
                return resolution;
            }
        }

        void SetResolution(const Resolution&);

        inline const bool IsFullscreen() const noexcept { return fullscreen; }
        void SetFullscreen(bool) noexcept;

        inline const bool GetVsync() const noexcept { return vsync; }
        void SetVSync(bool) noexcept;

        void CenterWindow() const noexcept;
        void Clear() noexcept;
        void Clear(const Colour&) noexcept;
    };
}

#endif