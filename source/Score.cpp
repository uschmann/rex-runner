#include "Score.h"
#include <string>

Score::Score(SDL_Renderer* renderer, TTF_Font* font) 
{
    mRenderer = renderer;
    mFont = font;
    mScore = 0;
    mHighScore = 0;
}

void Score::setScore(int score) 
{
    mScore = score;
}

void Score::setHighScore(int highScore) 
{
    mHighScore = highScore;
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

    sprintf(text, "Highscore: %d", mHighScore);
    surfaceMessage = TTF_RenderText_Solid(mFont, text, textColor);
    rect = { 1280 - surfaceMessage->w - 50, 50, surfaceMessage->w, surfaceMessage->h };
    texture = SDL_CreateTextureFromSurface(mRenderer, surfaceMessage);

    SDL_SetTextureAlphaMod(texture, 200);

    SDL_RenderCopy(mRenderer, texture, NULL, &rect);
    
    SDL_FreeSurface(surfaceMessage);
    SDL_DestroyTexture(texture);
}