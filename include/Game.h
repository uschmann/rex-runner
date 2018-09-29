#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "Trex.h"
#include "Cactus.h"
#include "Cloud.h"
#include "Ground.h"
#include "Score.h"

class Game
{
    public:
        Game(SDL_Renderer* renderer, SDL_Texture* sprites, TTF_Font* font);

        void reset();
        void update(int deltaTime);
        void draw();
        void pressButton();

        enum State {
            INTRO,
            RUNNING,
            GAME_OVER
        };
    private:
        static const int NUMBER_OF_CACTUSES = 2;
        static const int NUMBER_OF_CLOUDS = 4;
        static const int START_SPEED = 10;
        
        SDL_Renderer* mRenderer;
        SDL_Texture* mSprites;
        TTF_Font* mFont;

        Trex* mTrex;
        Cactus* mCactuses[Game::NUMBER_OF_CACTUSES];
        Cloud* mClouds[4];
        Ground* mGround;
        Score* mScore;

        int mSpeed;
        int mCurrentScore;
        Game::State mState;
};