
#include "Cactus.h"

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
    mBoundingBox = { 
        1280,
        Cactus::POS_Y - Cactus::FRAMES[mType].h * 2,
        Cactus::FRAMES[mType].w * 2,
        Cactus::FRAMES[mType].h * 2,
    };
}

void Cactus::move(int offset)
{
    mBoundingBox.x -= offset;

    if(mBoundingBox.x <= mBoundingBox.w * -1) {
        mBoundingBox.x = 1280;
    }
}

void Cactus::setX(int x)
{
    mBoundingBox.x = x;
}

void Cactus::draw()
{
    SDL_RenderCopy(mRenderer, mSprites, &Cactus::FRAMES[mType], &mBoundingBox);
}