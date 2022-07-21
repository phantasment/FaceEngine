#include "FaceEngine/Window.h"

namespace FaceEngine
{
    Window::Window(GraphicsDevice* d)
    {
        graphicsDevice = d;
        title = "Game";
        resolution = graphicsDevice->GetPrimaryDisplay().GetMinResolution();
        winHandle = glfwCreateWindow(resolution.GetWidth(), resolution.GetHeight(), title.c_str(), NULL, NULL);

        if (winHandle == NULL)
        {
            throw Exception::FromMessage("FaceEngine::Window::Window", "Couldn't create window.");
        }

        fullscreen = false;
        vsync = true;
        glfwSwapInterval(1);
        clearColour = Colour::Black;
    }

    void Window::Dispose() noexcept
    {
        glfwDestroyWindow(winHandle);
        winHandle = nullptr;
    }

    void Window::SetTitle(const std::string& t) noexcept
    {
        title = t;
        glfwSetWindowTitle(winHandle, title.c_str());
    }

    void Window::SetResolution(const Resolution& r)
    {
        const Resolution& min = graphicsDevice->GetPrimaryDisplay().GetMinResolution();
        const Resolution& max = graphicsDevice->GetPrimaryDisplay().GetMaxResolution();

        if (r.GetWidth() < min.GetWidth() || r.GetHeight() < min.GetHeight() ||
            r.GetWidth() > max.GetWidth() || r.GetHeight() > max.GetHeight())
        {
            throw Exception::FromMessage("FaceEngine::Window::SetResolution", "Invalid resolution.");
        }

        resolution = r;
        
        if (!fullscreen)
        {
            glfwSetWindowSize(winHandle, r.GetWidth(), r.GetHeight());
            glViewport(0, 0, r.GetWidth(), r.GetHeight());
        }
    }

    void Window::SetFullscreen(bool f) noexcept
    {
        fullscreen = f;
        const Display& display = graphicsDevice->GetPrimaryDisplay();
        const Resolution& res = display.GetMaxResolution();

        if (fullscreen)
        {
            glfwSetWindowMonitor(winHandle, display.GetHandle(), 0, 0, res.GetWidth(), res.GetHeight(), GLFW_DONT_CARE);
            glViewport(0, 0, res.GetWidth(), res.GetHeight());
        }
        else
        {
            glfwSetWindowMonitor(winHandle, NULL,
                                (res.GetWidth() - resolution.GetWidth()) / 2,
                                (res.GetHeight() - resolution.GetHeight()) / 2,
                                resolution.GetWidth(), resolution.GetHeight(), GLFW_DONT_CARE);
            glViewport(0, 0, resolution.GetWidth(), resolution.GetHeight());
        }
    }

    void Window::SetVSync(bool v) noexcept
    {
        vsync = v;
        glfwSwapInterval(vsync ? 1 : 0);
    }

    void Window::CenterWindow() const noexcept
    {
        if (!fullscreen)
        {
            const Resolution& res = graphicsDevice->GetPrimaryDisplay().GetMaxResolution();
            glfwSetWindowPos(winHandle, (res.GetWidth() - resolution.GetWidth()) / 2, (res.GetHeight() - resolution.GetHeight()) / 2);
        }
    }

    void Window::Clear() noexcept
    {
        Clear(Colour::Black);
    }

    void Window::Clear(const Colour& col) noexcept
    {
        if (clearColour != col)
        {
            clearColour = col;
            glClearColor(clearColour.GetR(), clearColour.GetG(), clearColour.GetB(), clearColour.GetA());
        }

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }
}