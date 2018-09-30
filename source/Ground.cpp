#include "Ground.h"

Ground::Ground(SDL_Renderer* renderer, SDL_Texture* sprites)
{
    mRenderer = renderer;
    mSprites = sprites;
    mRect1 = {
        0,
        Ground::GROUND_Y,
        Ground::SPRITE_WIDTH,
        Ground::SPRITE_HEIGHT
    };
    mRect2 = {
        Ground::SPRITE_WIDTH,
        Ground::GROUND_Y,
        Ground::SPRITE_WIDTH,
        Ground::SPRITE_HEIGHT
    };
}

const int Ground::GROUND_Y = 475;
const int Ground::SPRITE_X = 2;
const int Ground::SPRITE_Y = 54;
const int Ground::SPRITE_WIDTH = 1200;
const int Ground::SPRITE_HEIGHT = 12;
const SDL_Rect Ground::FRAME_SPRITE = {
    Ground::SPRITE_X,
    Ground::SPRITE_Y,
    Ground::SPRITE_WIDTH,
    Ground::SPRITE_HEIGHT,
};

void Ground::move(int offset)
{
    mRect1.x -= offset;
    mRect2.x -= offset;
    if(mRect1.x <= Ground::SPRITE_WIDTH * -1) {
        mRect1.x += Ground::SPRITE_WIDTH;
        mRect2.x += Ground::SPRITE_WIDTH;
    }
}

void Ground::draw()
{
    SDL_RenderCopy(mRenderer, mSprites, &Ground::FRAME_SPRITE, &mRect1);
    SDL_RenderCopy(mRenderer, mSprites, &Ground::FRAME_SPRITE, &mRect2);
}