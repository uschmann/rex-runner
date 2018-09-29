#include "Score.h"
#include <string>

Score::Score(SDL_Renderer* renderer, TTF_Font* font) 
{
    mRenderer = renderer;
    mFont = font;
    mScore = 0;
}

void Score::setScore(int score) 
{
    mScore = score;
}

void Score::draw()
{
    char text[500];
    sprintf(text, "Score: %d", mScore);

    SDL_Color textColor = { 0x53, 0x53, 0x53 };
    SDL_Surface* surfaceMessage = TTF_RenderText_Solid(mFont, text, textColor);
    SDL_Rect rect = { 50, 50, surfaceMessage->w, surfaceMessage->h };
    SDL_Texture* texture = SDL_CreateTextureFromSurface(mRenderer, surfaceMessage);

    SDL_RenderCopy(mRenderer, texture, NULL, &rect);

    SDL_FreeSurface(surfaceMessage);
    SDL_DestroyTexture(texture);
}