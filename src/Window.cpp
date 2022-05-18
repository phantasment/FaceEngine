#include "FaceEngine/Window.h"

namespace FaceEngine
{
    Window::Window(GraphicsDevice* d)
    {
        graphicsDevice = d;
        title = "Game";
        currentRes = graphicsDevice->GetPrimaryDisplay().MinResolution();
        winHandle = glfwCreateWindow(currentRes.GetWidth(), currentRes.GetHeight(), title.c_str(), NULL, NULL);

        if (winHandle == NULL)
        {
            throw Exception::FromMessage("FaceEngine::Window::Window", "Couldn't create window.");
        }

        fullscreen = false;
        vsync = true;
        glfwSwapInterval(1);
    }

    void Window::SetTitle(const std::string& t) noexcept
    {
        title = t;
        glfwSetWindowTitle(winHandle, title.c_str());
    }

    void Window::SetResolution(const Resolution& r)
    {
        const Resolution& min = graphicsDevice->GetPrimaryDisplay().MinResolution();
        const Resolution& max = graphicsDevice->GetPrimaryDisplay().MaxResolution();

        if (r.GetWidth() < min.GetWidth() || r.GetHeight() < min.GetHeight() ||
            r.GetWidth() > max.GetWidth() || r.GetHeight() > max.GetHeight())
        {
            throw Exception::FromMessage("FaceEngine::Window::SetResolution", "Invalid resolution.");
        }

        currentRes = r;
        
        if (!fullscreen)
        {
            glfwSetWindowSize(winHandle, r.GetWidth(), r.GetHeight());
            glViewport(0, 0, r.GetWidth(), r.GetHeight());
        }
    }

    void Window::SetVSync(const bool v) noexcept
    {
        vsync = v;
        glfwSwapInterval(vsync ? 1 : 0);
    }

    void Window::Clear() const noexcept
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }
}