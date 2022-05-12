/**
 * @file Game.h
 * @author Logan Woods
 * @brief A class containing the logic required to run a game.
 * @version 0.1
 * @date 2022-04-27
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef FACEENGINE_GAME_H_
#define FACEENGINE_GAME_H_

#include <atomic>

#include "FaceEngine/Exception.h"
#include "FaceEngine/Window.h"
#include "FaceEngine/ResourceManager.h"
#include "FaceEngine/ContentLoader.h"
#include "FaceEngine/Game/GameUpdate.h"
#include "FaceEngine/Game/GameDraw.h"

namespace FaceEngine
{
    class Game
    {
    private:
        std::atomic_bool GameRunning;
        void RunGame();
    protected:
        // The graphics device for a running game;
        GraphicsDevice* GraphicsDevicePtr;

        // Manages heap allocated resources such as textures, fonts, shaders, & sound.
        ResourceManager* ResourceManagerPtr;
        
        // The game window.
        Window* WindowPtr;

        // The content loader.
        ContentLoader* ContentLoaderPtr;
        
        // Contains ionformation important for updating a game such as input and delta time.
        GameUpdate* GameUpdatePtr;

        // Contains information important for drawing a game.
        GameDraw* GameDrawPtr;

        // Determines the target speed of the Update() function.
        // A value less than 1 indicates no limit.
        double PreferredUpdates = 0.0f;

        // Determines the target speed of the Draw() function.
        // A value less than 1 indicates no limit.
        double PreferredDraws = 0.0f;
    public:
        virtual void Initialise();
        virtual void Update();
        virtual void Draw();
        void Run();
        void Exit();
    };
}

#endif