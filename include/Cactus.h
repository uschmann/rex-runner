#pragma once

#include <SDL2/SDL.h>

class Cactus 
{
    public: 
        Cactus(SDL_Renderer* renderer, SDL_Texture* sprites, int type);

        void move(int offset);
        void draw();
        void setX(int x);
        SDL_Rect* getRect();
    private:
        SDL_Renderer* mRenderer;
        SDL_Texture* mSprites;
        
        SDL_Rect mSrcRect;
        SDL_Rect mBoundingBox;
        int mType;

        static const int POS_Y;
        static const SDL_Rect FRAMES[2];
        static const int SPRITE_WIDTH_SMALL;
        static const int SPRITE_HEIGHT_SMALL;
        static const int SPRITE_WIDTH_BIG;
        static const int SPRITE_HEIGHT_BIG;
};