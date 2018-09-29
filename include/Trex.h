#pragma once

#include <SDL2/SDL.h>

class Trex {
    public:
    Trex(SDL_Renderer* renderer, SDL_Texture* sprites);

    enum State {
        WALKING,
        JUMPING,
        CRASHED
    };

    void update(int deltaTime);
    void draw();

    void jump();
    private:
        static const SDL_Rect FRAMES_WALKING[2];
        static const SDL_Rect FRAME_JUMPING;
        static const SDL_Rect FRAME_CRASHED;
        static const int SPRITE_WIDTH;
        static const int SPRITE_HEIGHT;
        static const int SPRITE_POS_X;
        static const int SPRITE_POS_Y;

        static const int WIDTH;
        static const int HEIGHT;

        static const int GROUND_Y;
        static const float JUMP_VELOCITY;
        static const float GRAVITY_Y;

        SDL_Renderer* mRenderer;
        SDL_Texture* mSprites;
        Trex::State mState;

        int mX;
        int mTimer;
        int mLastFrameChange;
        int mCurrentWalkFrame;
        float mY;
        float mVelocityY;
};