#pragma once

#include <SDL2/SDL.h>

class Cloud 
{
    public:
        Cloud(SDL_Renderer* renderer, SDL_Texture* sprites);

        void move(int offset);
        void draw();
    private:
        SDL_Renderer* mRenderer;
        SDL_Texture* mSprites;

        SDL_Rect mRect;

        static const int MIN_Y;
        static const int MAX_Y;

        static const int SPRITE_X;
        static const int SPRITE_Y;
        static const int SPRITE_WIDTH;
        static const int SPRITE_HEIGHT;
};