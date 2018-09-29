#pragma once

#include <SDL2/SDL.h>

class Cactus 
{
    public: 
        Cactus(SDL_Renderer* renderer, SDL_Texture* sprites, int type);

        void move(int offset);
        void draw();
        void setX(int x);
    private:
        SDL_Renderer* mRenderer;
        SDL_Texture* mSprites;
    
        SDL_Rect mBoundingBox;
        int mType;


        static const int POS_Y;
        static const SDL_Rect FRAMES[2];
        static const int SPRITE_WIDTH_SMALL;
        static const int SPRITE_HEIGHT_SMALL;
        static const int SPRITE_WIDTH_BIG;
        static const int SPRITE_HEIGHT_BIG;
};


/*
            CACTUS_LARGE: { x: 652, y: 2 },
            CACTUS_SMALL: { x: 446, y: 2 },
*/