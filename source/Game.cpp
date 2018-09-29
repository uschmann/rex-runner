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
    mHighScore = 0;
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
    int speed = mSpeed;
    switch(mState) {
        case Game::State::INTRO:

        break;
        case Game::State::RUNNING:
            
            if(mCurrentScore > 500) {
                speed += 2;
            }
            if(mCurrentScore > 1000) {
                speed += 2;
            }
            if(mCurrentScore > 1500) {
                speed += 2;
            }
            if(mCurrentScore > 2000) {
                speed += 2;
            }
            if(mCurrentScore > 2500) {
                speed += 2;
            }


            mTrex->update(deltaTime);


            mGround->move(speed);

            for(int i = 0; i < Game::NUMBER_OF_CLOUDS; i++) {
                mClouds[i]->move(speed);
            }

            for(int i = 0; i < Game::NUMBER_OF_CACTUSES; i++) {
                mCactuses[i]->move(speed);
            }

            for(int i = 0; i < Game::NUMBER_OF_CACTUSES; i++) {
                if(mTrex->checkCollisions(mCactuses[i]->getRect())) {
                    mState = Game::State::GAME_OVER;
                    if(mCurrentScore > mHighScore) {
                        mHighScore = mCurrentScore;
                        mScore->setHighScore(mHighScore);
                    }
                }
            }

            if(mState == Game::State::RUNNING) {
                mCurrentScore ++;
                mScore->setScore(mCurrentScore);
            }
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

    if(mState == Game::State::GAME_OVER) {
        SDL_Rect srcRect = { 2, 2, 36, 32};
        SDL_Rect destRect = { 1280 / 2 - 32, 720 / 2 - 16, 36 * 2, 32 * 2};
        SDL_RenderCopy(mRenderer, mSprites, &srcRect, &destRect);

        SDL_Color textColor = { 0x53, 0x53, 0x53 };
        SDL_Surface* surfaceMessage = TTF_RenderText_Solid(mFont, "GAME OVER", textColor);
        SDL_Rect rect = { 1280 / 2 - (surfaceMessage->w / 2), 280, surfaceMessage->w, surfaceMessage->h };
        SDL_Texture* texture = SDL_CreateTextureFromSurface(mRenderer, surfaceMessage);
        SDL_RenderCopy(mRenderer, texture, NULL, &rect);
        SDL_FreeSurface(surfaceMessage);
        SDL_DestroyTexture(texture);
    }
}