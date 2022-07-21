#include "FaceEngine/GameUpdate.h"

namespace FaceEngine
{
    GameUpdate* GameUpdate::thisptr;
    
    void GameUpdate::KeyCallback(GLFWwindow*, int key, int scancode, int action, int mods)
    {
        thisptr->currentKeys[key] = action;

        if (action)
        {
            TypedKey typedKey
            {
                key,
                (bool)(mods & GLFW_MOD_SHIFT),
                (bool)(mods & GLFW_MOD_CONTROL),
                (bool)(mods & GLFW_MOD_ALT),
                (bool)(mods & GLFW_MOD_CAPS_LOCK)
            };
            thisptr->keysTyped.push_back(std::move(typedKey));
        }
    }

    void GameUpdate::MouseCallback(GLFWwindow*, int button, int action, int mods)
    {
        thisptr->currentMice[button] = action;
    }

    void GameUpdate::CursorPosCallback(GLFWwindow*, double xpos, double ypos)
    {
        thisptr->mousePos.X = (float)xpos;
        thisptr->mousePos.Y = (float)ypos;
    }

    GameUpdate::GameUpdate(GLFWwindow* gw) noexcept
    {
        winHandle = gw;
        previousKeys = new int[GLFW_KEY_LAST];
        currentKeys = new int[GLFW_KEY_LAST];

        for (int i = 0; i < GLFW_KEY_LAST; ++i)
        {
            previousKeys[i] = GLFW_RELEASE;
            currentKeys[i] = GLFW_RELEASE;
        }

        previousMice = new int[GLFW_MOUSE_BUTTON_LAST];
        currentMice  = new int[GLFW_MOUSE_BUTTON_LAST];

        for (int i = 0; i < GLFW_MOUSE_BUTTON_LAST; ++i)
        {
            previousMice[i] = GLFW_RELEASE;
            currentMice[i] = GLFW_RELEASE;
        }

        thisptr = this;
        glfwSetKeyCallback(winHandle, &KeyCallback);
        glfwSetMouseButtonCallback(winHandle, &MouseCallback);
        glfwSetCursorPosCallback(winHandle, &CursorPosCallback);
    }

    void GameUpdate::Dispose() noexcept
    {
        if (previousKeys == nullptr) { return; }
        
        delete[] previousKeys;
        delete[] currentKeys;
        delete[] previousMice;
        delete[] currentMice;
        previousKeys = nullptr;
    }

    void GameUpdate::UpdateInput() noexcept
    {
        for (int i = 0; i < GLFW_KEY_LAST; ++i)
        {
            previousKeys[i] = currentKeys[i];
        }

        for (int i = 0; i < GLFW_MOUSE_BUTTON_LAST; ++i)
        {
            previousMice[i] = currentMice[i];
        }

        keysTyped.clear();
    }

    bool GameUpdate::IsKeyDown(int key) const
    {
        if (key < 0 || key > GLFW_KEY_LAST)
        {
            throw Exception::FromMessage("FaceEngine::GameUpdate::IsKeyDown", "Invalid key.");
        }

        return currentKeys[key];
    }

    bool GameUpdate::IsKeyPressed(int key) const
    {
        if (key < 0 || key > GLFW_KEY_LAST)
        {
            throw Exception::FromMessage("FaceEngine::GameUpdate::IsKeyPressed", "Invalid key.");
        }

        return !previousKeys[key] && currentKeys[key];
    }

    bool GameUpdate::IsKeyReleased(int key) const
    {
        if (key < 0 || key > GLFW_KEY_LAST)
        {
            throw Exception::FromMessage("FaceEngine::GameUpdate::IsKeyReleased", "Invalid key.");
        }

        return previousKeys[key] && !currentKeys[key];
    }

    bool GameUpdate::IsMouseDown(int button) const
    {
        if (button < 0 || button > GLFW_MOUSE_BUTTON_LAST)
        {
            throw Exception::FromMessage("FaceEngine::GameUpdate::IsMouseDown", "Invalid button.");
        }

        return currentMice[button];
    }

    bool GameUpdate::IsMousePressed(int button) const
    {
        if (button < 0 || button > GLFW_MOUSE_BUTTON_LAST)
        {
            throw Exception::FromMessage("FaceEngine::GameUpdate::IsMousePressed", "Invalid button.");
        }

        return previousMice[button] && !currentMice[button];
    }

    bool GameUpdate::IsMouseReleased(int button) const
    {
        if (button < 0 || button > GLFW_MOUSE_BUTTON_LAST)
        {
            throw Exception::FromMessage("FaceEngine::GameUpdate::IsMouseReleased", "Invalid button.");
        }

        return previousMice[button] && !currentMice[button];
    }
}