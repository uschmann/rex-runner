#pragma once

#include <SDL2/SDL.h>

class Ground 
{
    public:
        Ground(SDL_Renderer* renderer, SDL_Texture* sprites);

        void move(int offset);
        void draw();

    private:
        SDL_Renderer* mRenderer;
        SDL_Texture* mSprites;

        SDL_Rect mRect1; 
        SDL_Rect mRect2;

        static const int GROUND_Y;
        static const int SPRITE_X;
        static const int SPRITE_Y;
        static const int SPRITE_WIDTH;
        static const int SPRITE_HEIGHT;
        static const SDL_Rect FRAME_SPRITE;

};