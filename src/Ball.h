#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

class Ball
{
public:
    // Initialize the ball
    Ball(int x, int y, int radius, int speed, int direction, SDL_Renderer* renderer);

    // Update the ball
    void update(SDL_Renderer* renderer, int SCREEN_WIDTH, int SCREEN_HEIGHT);

    // Clean the ball
    void clean();

    // Get the ball's position
    SDL_Rect getPosition();

    // Get the ball's radius
    int getRadius();

// Game variables

    // Ball's radius
    int mRadius;

    // Direction of the ball
    int mDirectionX;
    int mDirectionY;

    // Ball's position
    SDL_Rect mPosition;
    SDL_Texture *mTexture;

};