#include "Game.h"
#include "Score.h"

Game::Game(SDL_Renderer* renderer, SDL_Texture* sprites, TTF_Font* font)
{
    mRenderer = renderer;
    mSprites = sprites;
    mFont = font;

    mTrex = new Trex(mRenderer, mSprites);
    mGround = new Ground(mRenderer, mSprites);

    for(int i = 0; i < Game::NUMBER_OF_CLOUDS; i++) {
        mClouds[i] = new Cloud(mRenderer, mSprites);
    }

    for(int i = 0; i < Game::NUMBER_OF_CACTUSES; i++) {
        mCactuses[i] = new Cactus(mRenderer, mSprites, i % 2);
    }

    mScore = new Score(mRenderer, mFont);
    mScore->setScore(0);

    mSpeed = Game::START_SPEED;

    mState = Game::State::RUNNING;

    mCurrentScore = 0;
}

void Game::reset()
{
    mTrex->reset();
    for(int i = 0; i < Game::NUMBER_OF_CACTUSES; i++) {
        mCactuses[i]->setX(1200 + ((rand() % 3) * 1200));
    }
    mCurrentScore = 0;
    mState = Game::State::RUNNING;
}

void Game::pressButton()
{
    switch(mState) {
        case Game::State::INTRO:
            reset();
        break;
        case Game::State::RUNNING:
            mTrex->jump();
        break;
        case Game::State::GAME_OVER:
            reset();
        break;
    }
}

void Game::update(int deltaTime)
{
    switch(mState) {
        case Game::State::INTRO:

        break;
        case Game::State::RUNNING:
            mTrex->update(deltaTime);
            mGround->move(mSpeed);

            for(int i = 0; i < Game::NUMBER_OF_CLOUDS; i++) {
                mClouds[i]->move(mSpeed);
            }

            for(int i = 0; i < Game::NUMBER_OF_CACTUSES; i++) {
                mCactuses[i]->move(mSpeed);
            }

            for(int i = 0; i < Game::NUMBER_OF_CACTUSES; i++) {
                if(mTrex->checkCollisions(mCactuses[i]->getRect())) {
                    mState = Game::State::GAME_OVER;
                }
            }

            mCurrentScore += mSpeed / 4;
            mScore->setScore(mCurrentScore);
        break;
        case Game::State::GAME_OVER:

        break;
    }
}

void Game::draw()
{
    mGround->draw();

    for(int i = 0; i < Game::NUMBER_OF_CLOUDS; i++) {
        mClouds[i]->draw();
    }

    for(int i = 0; i < Game::NUMBER_OF_CACTUSES; i++) {
        mCactuses[i]->draw();
    }

    mTrex->draw();
    mScore->draw();
}