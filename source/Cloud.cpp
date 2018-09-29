
#include "Cloud.h"

const int Cloud::MIN_Y = 50;
const int Cloud::MAX_Y = 300;

const int Cloud::SPRITE_X = 86;
const int Cloud::SPRITE_Y = 2;
const int Cloud::SPRITE_WIDTH = 46;
const int Cloud::SPRITE_HEIGHT = 14;

Cloud::Cloud(SDL_Renderer* renderer, SDL_Texture* sprites)
{
    mRenderer = renderer;
    mSprites = sprites;

    mRect = {
        rand() % (1200-100 + 1) + 100,
        rand() % (Cloud::MAX_Y - Cloud::MIN_Y + 1) + Cloud::MIN_Y,
        Cloud::SPRITE_WIDTH * 2,
        Cloud::SPRITE_HEIGHT * 2
    };
}

void Cloud::move(int offset) 
{
    mRect.x -= offset / 2;

    if(mRect.x <= mRect.w * -1) {
        mRect.x = 1200 + (rand() % (1200-100 + 1) + 100);
        mRect.y = rand() % (Cloud::MAX_Y - Cloud::MIN_Y + 1) + Cloud::MIN_Y;
    }
}

void Cloud::draw() 
{
    SDL_Rect srcRect = {
        Cloud::SPRITE_X,
        Cloud::SPRITE_Y,
        Cloud::SPRITE_WIDTH,
        Cloud::SPRITE_HEIGHT
    };

    SDL_RenderCopy(mRenderer, mSprites, &srcRect, &mRect);
}