#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

class Score
{
    public:
        Score(SDL_Renderer* renderer, TTF_Font* font);
        void setScore(int score);
        void draw();
    private:
        SDL_Renderer* mRenderer;
        TTF_Font* mFont;

        int mScore;
};