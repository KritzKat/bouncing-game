#include "Ball.h"

// Initialize the ball
Ball::Ball(int x, int y, int radius, int speed, int direction, SDL_Renderer* renderer)
{
    // Set the ball's position
    mPosition.x = x;
    mPosition.y = y;
    mPosition.w = radius * 2;
    mPosition.h = radius * 2;

    // Set the directions
    mDirectionX = direction;
    mDirectionY = direction;

    // Set the ball's radius
    mRadius = radius;

    // Load the ball's texture
    mTexture = IMG_LoadTexture(renderer, "textures/smiles.png");
    if (mTexture == NULL)
    {
        printf("Unable to load image! SDL_image Error: %s\n", IMG_GetError());
        exit(1);
    }
}

// Update the ball
void Ball::update(SDL_Renderer* renderer, int SCREEN_WIDTH, int SCREEN_HEIGHT)
{
    //TODO: figure out collision lol
    
    // Move the ball using a state machine. Also check if it hits the side or bottom to switch direction
    switch (mDirectionX)
    {
        case 0:
            mPosition.x += 1;
            if (mPosition.x >= SCREEN_WIDTH - (mRadius * 2))
            {
                mDirectionX = 1;
            }
            break;
        case 1:
            mPosition.x -= 1;
            if (mPosition.x <= 0)
            {
                mDirectionX = 0;
            }
            break;
    }
    // cases for the Y component
    switch (mDirectionY)
    {
        case 0:
            mPosition.y += 1;
            if (mPosition.y >= SCREEN_HEIGHT - (mRadius * 2))
            {
                mDirectionY = 1;
            }
            break;
        case 1:
            mPosition.y -= 1;
            if (mPosition.y <= 0)
            {
                mDirectionY = 0;
            }
            break;
    }

    // Make sure the ball doesnt go out of bounds when resizing
    if (mPosition.x < 0)
    {
        mPosition.x = 0;
    }
    if (mPosition.y < 0)
    {
        mPosition.y = 0;
    }
    if (mPosition.x > SCREEN_WIDTH - (mRadius * 2))
    {
        mPosition.x = SCREEN_WIDTH - (mRadius * 2);
    }
}

void Ball::clean()
{
    // Free the texture
    SDL_DestroyTexture(mTexture);
    mTexture = NULL;
}