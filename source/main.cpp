#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <curl/curl.h>
#include <string>
#include <switch.h>

#include "Game.h"

#define DEBUG 

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
SDL_Surface* screen = NULL;
SDL_Texture* sprites = NULL;
TTF_Font* font = NULL;

int screenWidth = 0;
int screenHeight = 0;

/**
 * Init
 */
bool init() {
  SDL_Init(SDL_INIT_EVERYTHING);

  SDL_InitSubSystem(SDL_INIT_JOYSTICK);
  SDL_JoystickEventState(SDL_ENABLE);
  SDL_JoystickOpen(0);
  TTF_Init();

  romfsInit();

  #ifdef DEBUG
  socketInitializeDefault();
  nxlinkStdio();
  printf("printf output now goes to nxlink server\n");
  #endif // DEBUG

  window = SDL_CreateWindow(nullptr, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 0, 0, SDL_WINDOW_FULLSCREEN_DESKTOP);
  if (!window) {
    printf("SDL_CreateWindow() failed!\n");
    SDL_Quit();
    return false;
  }

  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
  if (!renderer) {
    printf("SDL_CreateRenderer() failed!\n");
    SDL_Quit();
    return false;
  }

  screen = SDL_GetWindowSurface(window);
  if (!screen) {
    printf("SDL_GetWindowSurface() failed!\n");
    SDL_Quit();
    return false;
  }

  sprites = IMG_LoadTexture(renderer ,"romfs:/sprites.png");
  if (!sprites) {
    printf("IMG_LoadTexture() failed!\n");
    SDL_Quit();
    return false;
  }

  font = TTF_OpenFont("romfs:/font.ttf", 32);
  if(!font) {
    printf("TTF_OpenFont() failed!\n");
    SDL_Quit();
    return false;
  }

  SDL_GetWindowSize(window, &screenWidth, &screenHeight);
  printf("ScreenWidth: %d, ScreenHeight: %d\n", screenWidth, screenHeight);

  return true;
}

/**
 * Main entrypoint
 */
int main(int argc, char* argv[]) {
  if(!init()) {
    #ifdef DEBUG
      socketExit();
    #endif // DEBUG
    return 0;
  }
  bool isRunning = true;
  int lastTick = SDL_GetTicks();

  Game* game = new Game(renderer, sprites, font);

  SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
  SDL_RenderClear(renderer);
  SDL_RenderPresent(renderer);

  while (isRunning) {
    int currentTick = SDL_GetTicks();
    int deltaTime = currentTick - lastTick;
    lastTick = currentTick;

    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_JOYBUTTONDOWN:
              switch(event.jbutton.button) {
                case SDL_CONTROLLER_BUTTON_A:
                  game->pressButton();
                break;
                case SDL_CONTROLLER_BUTTON_X:
                  isRunning = false;
                break;
              }
            break;
            case SDL_FINGERDOWN:
                game->pressButton();
                break;
        }
    }

    game->update(deltaTime);

    SDL_RenderClear(renderer);
    game->draw();    
    SDL_RenderPresent(renderer);
  }

  SDL_FreeSurface(screen);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);

  #ifdef DEBUG
    socketExit();
  #endif // DEBUG
  

  SDL_Quit();
  return 0;
}
