
#include "Cactus.h"
#include <iostream>

const int Cactus::POS_Y = 500;

const int Cactus::SPRITE_WIDTH_SMALL = 17;
const int Cactus::SPRITE_HEIGHT_SMALL = 35;
const int Cactus::SPRITE_WIDTH_BIG = 25;
const int Cactus::SPRITE_HEIGHT_BIG = 50;

const SDL_Rect Cactus::FRAMES[2] = {
    { 228, 2, Cactus::SPRITE_WIDTH_SMALL, Cactus::SPRITE_HEIGHT_SMALL },
    { 332, 2, Cactus::SPRITE_WIDTH_BIG, Cactus::SPRITE_HEIGHT_BIG }
};

Cactus::Cactus(SDL_Renderer* renderer, SDL_Texture* sprites, int type)
{
    mRenderer = renderer;
    mSprites = sprites;

    mType = type;
    mSrcRect = { 
        Cactus::FRAMES[mType].x + (rand() % 5) * Cactus::FRAMES[mType].w,
        Cactus::FRAMES[mType].y,
        Cactus::FRAMES[mType].w,
        Cactus::FRAMES[mType].h
    };

    mBoundingBox = { 
        1280,
        Cactus::POS_Y - Cactus::FRAMES[mType].h * 2,
        Cactus::FRAMES[mType].w * 2,
        Cactus::FRAMES[mType].h * 2,
    };
}

SDL_Rect* Cactus::getRect() 
{
    return &mBoundingBox;
}

void Cactus::move(int offset)
{
    mBoundingBox.x -= offset;

    if(mBoundingBox.x <= mBoundingBox.w * -1) {
        mBoundingBox.x = 1280 + (rand() % 1000);
        mSrcRect.x = Cactus::FRAMES[mType].x  + (rand() % 5) * Cactus::FRAMES[mType].w;
    }
}

void Cactus::setX(int x)
{
    mBoundingBox.x = x;
}

void Cactus::draw()
{
    SDL_RenderCopy(mRenderer, mSprites, &mSrcRect, &mBoundingBox);
}