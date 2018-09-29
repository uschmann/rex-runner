#include "Trex.h"
#include <iostream>

const int Trex::SPRITE_POS_X = 848;
const int Trex::SPRITE_POS_Y = 2;

const SDL_Rect Trex::FRAMES_WALKING[2] = {
    { Trex::SPRITE_POS_X + 88, Trex::SPRITE_POS_Y, Trex::SPRITE_WIDTH, Trex::SPRITE_HEIGHT },
    { Trex::SPRITE_POS_X + 132, Trex::SPRITE_POS_Y, Trex::SPRITE_WIDTH, Trex::SPRITE_HEIGHT }
};

const SDL_Rect Trex::FRAME_JUMPING = { 
    Trex::SPRITE_POS_X, 
    Trex::SPRITE_POS_Y, 
    Trex::SPRITE_WIDTH, 
    Trex::SPRITE_HEIGHT 
};

const SDL_Rect Trex::FRAME_CRASHED = { 
    Trex::SPRITE_POS_X + 220, 
    Trex::SPRITE_POS_Y, 
    Trex::SPRITE_WIDTH, 
    Trex::SPRITE_HEIGHT 
};

const int Trex::SPRITE_WIDTH = 44;
const int Trex::SPRITE_HEIGHT = 47;

const int Trex::WIDTH = 88;
const int Trex::HEIGHT = 94;

const int Trex::GROUND_Y = 400;

const float Trex::JUMP_VELOCITY = -20;
const float Trex::GRAVITY_Y = 1;

Trex::Trex(SDL_Renderer* renderer, SDL_Texture* sprites) 
{
    mRenderer = renderer;
    mSprites = sprites;
    mState = Trex::State::WALKING;

    mX = 50;
    mY = Trex::GROUND_Y;
    mVelocityY = 0;
    mTimer = 0;
    mCurrentWalkFrame = 0;
    mLastFrameChange = 0;
}

void Trex::jump()
{
    if(mState == Trex::State::WALKING) {
        mState = Trex::State::JUMPING;
        mVelocityY = Trex::JUMP_VELOCITY;
    }
}

void Trex::update(int deltaTime)
{
    mTimer += deltaTime;

    switch(mState) {
        case Trex::State::WALKING:
            printf("Walking!\n");
            if(mTimer - mLastFrameChange > 200) {
                mLastFrameChange = mTimer;
                mCurrentWalkFrame = mCurrentWalkFrame == 0 ? 1 : 0;
            }
        break;
        case Trex::State::JUMPING:
            printf("Jumping!\n");
            mY += mVelocityY;
            mVelocityY += Trex::GRAVITY_Y;

            if(mY > Trex::GROUND_Y) {
                mY = Trex::GROUND_Y;
                mState = Trex::State::WALKING;
            }
        break;
        case Trex::State::CRASHED:
            printf("Crashed!\n");
        break;
    }
}

void Trex::draw() 
{
    SDL_Rect destRect = {
        mX,
        (int) mY,
        Trex::WIDTH,
        Trex::HEIGHT,
    };
    
    switch(mState) {
        case Trex::State::WALKING:
            SDL_RenderCopy(mRenderer, mSprites, &Trex::FRAMES_WALKING[mCurrentWalkFrame], &destRect);
        break;
        case Trex::State::JUMPING:
            SDL_RenderCopy(mRenderer, mSprites, &Trex::FRAME_JUMPING, &destRect);
        break;
        case Trex::State::CRASHED:
            SDL_RenderCopy(mRenderer, mSprites, &Trex::FRAME_CRASHED, &destRect);
        break;
    }

}