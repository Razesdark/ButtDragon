#include <SDL2/SDL.h>
#include <iostream>
#include <string>

#include "level.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int initialize_game(int, int);
void run_game();
void end_game();

SDL_Window* window = NULL;
SDL_Surface* screenSurface = NULL;

int main() {
  // ----------------------------------------------------------
  // Game Name: xX Space Race 2k Xx
  // Tagline: You're an hero, riding a dragon pooping on energyballs in Space
  // ----------------------------------------------------------

  // --------------------------------------------------------
  //  Initializes the game engine.
  //  This function is called from main.cpp, and will set the size of the screen
  // --------------------------------------------------------

  // Initialize SDL
  if ( SDL_Init( SDL_INIT_VIDEO ) < 0 ) {
    printf("SDL Could not initalize! ER: %s\n", SDL_GetError());
    return 1;
  }

  window = SDL_CreateWindow(  "Tjosegame",
                              SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED,
                              SCREEN_WIDTH,
                              SCREEN_HEIGHT,
                              SDL_WINDOW_SHOWN
                           );

  if (window == NULL) {
    printf("Could not create window! ER: %s\n", SDL_GetError() );
    return 0;
  } else {
    screenSurface = SDL_GetWindowSurface( window );
    SDL_FillRect( screenSurface, NULL, SDL_MapRGB( screenSurface->format, 0xFF, 0xFF, 0xFF ) );
    SDL_UpdateWindowSurface( window );
  }


  //  initialize_assets();
  //  run_game();
  //  end_game();

  int x = 4;


  while(x < 10) {
    Level* l = new Level(window, screenSurface, x+1);
    l->InitializeAssets();
    while(l->is_running) {
      l->GameTick();
    }
    l->EndLevel();

    x += 1;
    if(l->shut_down) {
      break;
    }
  }

}
