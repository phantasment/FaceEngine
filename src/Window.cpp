#include "FaceEngine/Window.h"

namespace FaceEngine
{
    Window::Window(GraphicsDevice* d)
    {
        graphicsDevice = d;
        title = "Game";
        currentRes = graphicsDevice->PrimaryDisplay().MinResolution();
        winHandle = glfwCreateWindow(currentRes.GetWidth(), currentRes.GetHeight(), title.c_str(), NULL, NULL);

        if (winHandle == NULL)
        {
            throw Exception::FromMessage("FaceEngine::Window::Window", "Couldn't create window.");
        }

        vsync = true;
        glfwSwapInterval(1);
    }

    void Window::SetTitle(const std::string& t) noexcept
    {
        title = t;
        glfwSetWindowTitle(winHandle, title.c_str());
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