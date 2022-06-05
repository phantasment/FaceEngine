/**
 * @file Game.h
 * @author Logan Woods
 * @brief A class containing the logic required to run a game.
 * @version 0.1
 * @date 2022-05-15
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
#include "FaceEngine/GameUpdate.h"
#include "FaceEngine/GameDraw.h"
#include "FaceEngine/AudioDevice.h"

namespace FaceEngine
{
    /**
     * @brief The object responsible for running the game's code.
     * 
     * This object should be inherited and the game's logic should be implemented by overriding the Initialise(), Update(), and Draw() functions.
     */
    class Game
    {
    private:
        static std::atomic_bool GameRunning;
    protected:
        /**
         * @brief An interface for the graphics capabilities for the current computer.
         * 
         * This object's allocation is automatic.
         */
        GraphicsDevice* GraphicsDevicePtr;

        /**
         * @brief A manager for heap-allocated objects used for the game.
         * 
         * This object's allocation is automatic.
         */
        ResourceManager* ResourceManagerPtr;
        
        /**
         * @brief An interface for the game window.
         * 
         * This object's allocation is automatic.
         */
        Window* WindowPtr;

        /**
         * @brief Loads game content from Face Engine content files.
         * 
         * This object's allocation is automatic.
         */
        ContentLoader* ContentLoaderPtr;
        
        /**
         * @brief Contains information used for updating a game.
         * 
         * This object's allocation is automatic.
         */
        GameUpdate* GameUpdatePtr;

        /**
         * @brief Contains information used for drawing a game.
         * 
         * This object's allocation is automatic.
         */
        GameDraw* GameDrawPtr;

        /**
         * @brief Used to play audio.
         * 
         * This object's allocation is automatic.
         */
        AudioDevice* AudioDevicePtr;

        /**
         * @brief Determines the target speed of the Update() function. A value less than 1 indicates no limit.
         */
        double PreferredUpdates = 0.0f;

        /**
         * @brief Determines the target speed of the Draw() function. A value less than 1 indicates no limit.
         */
        double PreferredDraws = 0.0f;
    public:
        /**
         * @brief Code to execute before the game starts running.
         * 
         * This function should never be called manually.
         */
        virtual void Initialise();

        /**
         * @brief Code to execute before the game exits.
         * 
         * This function should never be called manually.
         */
        virtual void OnExit();

        /**
         * @brief Code responsible for updating the game such as physics, input, etc.
         * 
         * This function should never be called manually.
         */
        virtual void Update();

        /**
         * @brief Code responsible for drawing the game.
         * 
         * This function should never be called manually.
         */
        virtual void Draw();

        /**
         * @brief Runs the game on the current thread.
         * 
         * An exception will be thrown if an error occurs while setting up the graphics environment.
         */
        void Run();

        /**
         * @brief Once called, the game will close after finishing the current tick.
         */
        void Exit();
    };
}

#endif