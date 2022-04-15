#include "Game.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string>
#include <iostream>

// init fucntion from Game.hpp
void Game::init()
{
    // Initialize SDL
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {

        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        exit(1);
    }
    else
    {
        // Create window and make it resizable 
        gWindow = SDL_CreateWindow("Bouncing Ball", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_RESIZABLE);
        // Check if our window exists
        if (gWindow == NULL)
        {
            printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
            exit(1);
        }
        else
        {
            // Create renderer for window
            gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
            // Check if renderer was created
            if (gRenderer == NULL)
            {
                printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
                exit(1);
            }
            else
            {
                // Set renderer draw color to white
                SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
                // Initialize PNG loading
                int imgFlags = IMG_INIT_PNG;
                if (!(IMG_Init(imgFlags) & imgFlags))
                {
                    printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
                    exit(1);
                }
            }
        }
    }
}

// run function
void Game::run()
{  
    //Create a new ball and add it to the vector
    balls.push_back(Ball(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 64, 1, 1, gRenderer));

    //Create a timer to control the animation
    Uint32 start;
    Uint32 delay = 1000 / 60;
    // Start the timer
    start = SDL_GetTicks();

    // Game loop
    while (!quit)
    {
        // Handle events on queue
        SDL_Event e;
        while (SDL_PollEvent(&e) != 0)
        {
            // Switch statement for all events
            switch (e.type)
            {
            case SDL_QUIT:
                quit = true;
                break;
            case SDL_MOUSEBUTTONDOWN:
                //If the left mouse button was pressed
                if (e.button.button == SDL_BUTTON_LEFT)
                {
                    //Get the mouse offsets
                    int x = e.button.x;
                    int y = e.button.y;
                    //Add a new ball at the mouse position
                    balls.push_back(Ball(x, y, 64, 1, 1, gRenderer));
                    // print out x and y
                    std::cout << "x: " << x << " y: " << y << std::endl;
                }
                break;
            // implement screen resizing
            case SDL_WINDOWEVENT:
                if (e.window.event == SDL_WINDOWEVENT_RESIZED)
                {
                    // Get new window size
                    int w, h;
                    SDL_GetWindowSize(gWindow, &w, &h);
                    // Set new window size
                    SCREEN_WIDTH = w;
                    SCREEN_HEIGHT = h;
                }
                break;
            }
        }

        // Clear screen
        SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(gRenderer);
        // Check the timer and update the balls vector
        if (SDL_GetTicks() - start >= delay)
        {
            for (int i = 0; i < balls.size(); i++)
            {
                balls[i].update(gRenderer, SCREEN_WIDTH, SCREEN_HEIGHT);
            }
            start = SDL_GetTicks();
        }
        // Copy all the balls to the renderer
        for(int i = 0; i < balls.size(); i++)
        {
            // Update the ball's texture
            SDL_RenderCopy(gRenderer, balls[i].mTexture, NULL, &balls[i].mPosition);
        }

        // Update the screen
        SDL_RenderPresent(gRenderer);
    }
}

// clean function
void Game::clean()
{
    // Free balls vector
    for (int i = 0; i < balls.size(); i++)
    {
        balls[i].clean();
    }
    balls.clear();
    // Free resources and close SDL
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;
    gRenderer = NULL;
    SDL_Quit();
}