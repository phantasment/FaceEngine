#include "FaceEngine/OGL.h"
#include "FaceEngine/Game.h"

namespace FaceEngine
{
    std::atomic_bool Game::GameRunning(false);

    void Game::Initialise() { }
    void Game::OnExit() { }
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

        GLFWwindow* winHandle = WindowPtr->winHandle;
        glfwMakeContextCurrent(winHandle);

        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            delete WindowPtr;
            delete GraphicsDevicePtr;
            glfwTerminate();
            throw Exception::FromMessage("FaceEngine::Game::Run", "Could not load OpenGL functions.");
        }

        glViewport(0, 0, WindowPtr->resolution.GetWidth(), WindowPtr->resolution.GetHeight());
        ResourceManagerPtr = new ResourceManager;
        ResourceManagerPtr->TrackResource(WindowPtr);
        ResourceManagerPtr->TrackResource(GraphicsDevicePtr);
        ResourceManagerPtr->TrackResource(ContentLoaderPtr = new ContentLoader(ResourceManagerPtr));
        ResourceManagerPtr->TrackResource(GameUpdatePtr = new GameUpdate(winHandle));
        ResourceManagerPtr->TrackResource(GameDrawPtr = new GameDraw);
        ResourceManagerPtr->TrackResource(AudioDevicePtr = new AudioDevice);

        // initialise
        Initialise();
        glfwShowWindow(winHandle);
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

        double now = glfwGetTime();

        // UPS/FPS stuff
        std::uint32_t updates = 0, frames = 0;
        double lastUPS = now;
        double lastFPS = now;

        // timing
        double lastUpdate = now;
        double lastDraw = now;
        double accumulator = 0.0;
        double frameTime;
        double refreshRate = (double)glfwGetVideoMode(glfwGetPrimaryMonitor())->refreshRate;
        float dt;

        while (!glfwWindowShouldClose(winHandle))
        {
            now = glfwGetTime();

            if (PreferredUpdates > 0.0)
            {
                dt = 1.0 / PreferredUpdates;
                frameTime = now - lastUpdate;

                if (frameTime > 0.25) { frameTime = 0.25; }

                lastUpdate = now;
                accumulator += frameTime;

                while (accumulator >= dt)
                {
                    GameUpdatePtr->delta = dt;
                    GameUpdatePtr->UpdateInput();
                    glfwPollEvents();
                    Update();
                    accumulator -= dt;
                    ++updates;
                }
            }
            else
            {
                GameUpdatePtr->delta = now - lastUpdate;
                lastUpdate = now;
                GameUpdatePtr->UpdateInput();
                glfwPollEvents();
                Update();
                ++updates;
            }

            // handle drawing
            now = glfwGetTime();
            GameDrawPtr->alpha = accumulator / dt;

            if (WindowPtr->vsync)
            {
                if (now - lastDraw >= 1.0 / refreshRate)
                {
                    GameDrawPtr->delta = now - lastDraw;
                    lastDraw = now;
                    Draw();
                    ++frames;
                    glfwSwapBuffers(winHandle);
                }
            }
            else if (PreferredDraws > 0.0)
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
        }
        
        OnExit();
        ResourceManagerPtr->DisposeAllResources();
        delete ResourceManagerPtr;
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