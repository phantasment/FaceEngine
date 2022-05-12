#include "FaceEngine/OGL.h"
#include "FaceEngine/Game.h"

namespace FaceEngine
{
    std::atomic_bool Game::GameRunning(false);
    
    void Game::Initialise() { }
    void Game::Update() { }
    void Game::Draw() { }

    void Game::Run()
    {
        bool running = false;

        if (!GameRunning.compare_exchange_strong(running, true))
        {
            throw Exception::FromMessage("FaceEngine::Game::Run", "Game is already running.");
        }
        else if (!glfwInit())
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

        glfwMakeContextCurrent(WindowPtr->winHandle);

        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            delete GraphicsDevicePtr;
            delete WindowPtr;
            glfwTerminate();
            throw Exception::FromMessage("FaceEngine::Game::Run", "Could not load OpenGL functions.");
        }

        GLFWwindow* winHandle = WindowPtr->winHandle;
        ResourceManagerPtr = new ResourceManager;
        ContentLoaderPtr = new ContentLoader(ResourceManagerPtr);
        GameUpdatePtr = new GameUpdate;
        GameDrawPtr = new GameDraw;

        // delta time/target time stuff
        double lastUpdate = glfwGetTime();
        double lastDraw = lastUpdate;
        double lastCleanup = lastDraw;
        double now;

        // UPS/FPS stuff
        std::uint32_t updates = 0, frames = 0;
        double lastUPS = lastCleanup;
        double lastFPS = lastUPS;

        Initialise();
        glfwShowWindow(winHandle);
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

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
                    ++updates;
                }
            }
            else
            {
                GameUpdatePtr->delta = now - lastUpdate;
                lastUpdate = now;
                Update();
                ++updates;
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
                    ++frames;
                    glfwSwapBuffers(winHandle);
                }
            }
            else
            {
                GameDrawPtr->delta = now - lastDraw;
                lastDraw = now;
                Draw();
                ++frames;
                glfwSwapBuffers(winHandle);
            }

            // UPS/FPS check
            now = glfwGetTime();

            if (now - lastUPS >= 1.0)
            {
                lastUPS = now;
                GameUpdatePtr->ups = updates;
                updates = 0;
            }

            if (now - lastFPS >= 1.0)
            {
                lastFPS = now;
                GameDrawPtr->fps = frames;
                frames = 0;
            }

            // do cleanup
            
            if (now - lastCleanup >= 1.0)
            {
                lastCleanup = now;
                ResourceManagerPtr->HandleMarked();
            }
        }
        
        ResourceManagerPtr->DisposeAllResources();
        delete ResourceManagerPtr;
        delete ContentLoaderPtr;
        delete GameUpdatePtr;
        delete GameDrawPtr;
        delete WindowPtr;
        delete GraphicsDevicePtr;
        glfwTerminate();
        GameRunning.store(false);
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