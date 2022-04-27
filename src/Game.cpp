#include "FaceEngine/OGL.h"
#include "FaceEngine/Game.h"

namespace FaceEngine
{
    void Game::Initialise() { }
    void Game::Update() { }
    void Game::Draw() { }

    void Game::Run()
    {
        if (!glfwInit())
        {
            throw Exception::FromMessage("FaceEngine::Game::Run", "Couldn't initialise GLFW.");
        }

        glfwDefaultWindowHints();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
        glfwWindowHint(GLFW_FOCUS_ON_SHOW, GLFW_TRUE);
    #ifdef __APPLE__
        #warning imagine being an apple user
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    #endif

        GraphicsDevicePtr = new GraphicsDevice;

        try
        {
            WindowPtr = new Window(GraphicsDevicePtr);
        }
        catch (const Exception& e)
        {
            delete GraphicsDevicePtr;
            glfwTerminate();
            throw e;
        }

        GLFWwindow* winHandle = WindowPtr->winHandle;
        ResourceManagerPtr = new ResourceManager;
        GameUpdatePtr = new GameUpdate;
        GameDrawPtr = new GameDraw;

        double lastUpdate = glfwGetTime();
        double lastDraw = lastUpdate;
        double lastCleanup = lastDraw;
        double now;

        Initialise();
        glfwShowWindow(winHandle);

        while (!glfwWindowShouldClose(winHandle))
        {
            // handle updating
            glfwPollEvents();
            now = glfwGetTime();

            if (PreferredUpdates > 0.0)
            {
                if (now - lastUpdate >= 1.0 / PreferredUpdates)
                {
                    GameUpdatePtr->delta = now - lastUpdate;
                    lastUpdate = now;
                    Update();
                }
            }
            else
            {
                GameUpdatePtr->delta = now - lastUpdate;
                lastUpdate = now;
                Update();
            }

            // handle drawing
            now = glfwGetTime();

            if (PreferredDraws > 0.0)
            {
                if (now - lastDraw >= 1.0 / PreferredDraws)
                {
                    GameDrawPtr->delta = now - lastDraw;
                    lastDraw = now;
                    Draw();
                    glfwSwapBuffers(winHandle);
                }
            }
            else
            {
                GameDrawPtr->delta = now - lastDraw;
                lastDraw = now;
                Draw();
                glfwSwapBuffers(winHandle);
            }

            // do cleanup
            now = glfwGetTime();

            if (now - lastCleanup >= 1.0)
            {
                lastCleanup = now;
                ResourceManagerPtr->HandleMarked();
            }
        }
        
        ResourceManagerPtr->DisposeAllResources();
        delete ResourceManagerPtr;
        delete GameUpdatePtr;
        delete GameDrawPtr;
        delete WindowPtr;
        delete GraphicsDevicePtr;
        glfwTerminate();
    }

    void Game::Exit()
    {
        if (GameRunning.load())
        {
            glfwSetWindowShouldClose(WindowPtr->winHandle, GLFW_TRUE);
        }
        else
        {
            throw Exception::FromMessage("FaceEngine::Game::Exit", "Game is not running!");
        }
    }
}