#pragma once
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "Ball.h"
#include <stdio.h>
#include <vector>

// Init, run and clean the game functions
class Game
{
public:

    // Initialize the game
    void init();

    // Run the game
    void run();

    // Clean the game
    void clean();

private:
    // Window and Renderer needed to do game stuff
    SDL_Window* gWindow;
    SDL_Renderer* gRenderer;

    // Screen window and height
    int SCREEN_WIDTH = 640;
    int SCREEN_HEIGHT = 480;
    
    // Game loop boolean
    bool quit = false;

    // Vector to hold ballls
    std::vector<Ball> balls;
};