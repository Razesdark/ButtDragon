#include <iostream>
#include <string>
#include <SDL2/SDL.h>

#include "game.h"
#ifndef GAME_ENTITY
  #include "game_entity.h"
#endif
#include "stars.h"

#include "player.h"
using namespace std;



bool game_running = true;

SDL_Window* window = NULL;
SDL_Surface* screenSurface = NULL;
SDL_Event e;

Player* player;
Star stars[STARS_ON_SCREEN];
void inline game_loop();

int initialize_game(int SCREEN_HEIGHT, int SCREEN_WIDTH) {
  // --------------------------------------------------------
  //  Initializes the game engine.
  //  This function is called from main.cpp, and will set the size of the screen
  // --------------------------------------------------------

  // Initialize SDL
  if ( SDL_Init( SDL_INIT_EVERYTHING ) < 0 ) {
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

  return 0;
}
void initialize_assets() {
  player = new Player();
  player->SetWindow(screenSurface);
  player->SetSprite("assets/spacedragon1.bmp", true);
  player->Activate();


  // Initialize Background assets
  for(int i = 0; i < STARS_ON_SCREEN; i++) {
    stars[i].PostInitialize(screenSurface);
  }

}

void run_game() {
  while(game_running) {
    game_loop();
  }
}
void end_game() {
  SDL_Delay( 1000 );
  SDL_DestroyWindow( window );
  SDL_Quit();
}

void check_keyboard() {
  // Allow loop to quit when SDL sends Quit event
  while( SDL_PollEvent( &e ) != 0) {
    switch(e.type) {
      case SDL_QUIT:
        printf("QUITTING\r\n");
        game_running = false;
      case SDL_KEYDOWN:
      case SDL_KEYUP:
        player->KeyboardEvent( &e.key );
      default:
        break;
    }
  }
}

void inline game_loop() {
    // Blank the entire screen
    SDL_FillRect( screenSurface, NULL, SDL_MapRGB( screenSurface->format, 0x12, 0x12, 0x13 ) ); // Sets Background color, #121213

    // Resolve Background assets first
    for(int i = 0; i < STARS_ON_SCREEN; i++)
      stars[i].Resolve();


    // Resolves player and players projectiles
    player->Resolve();

    // Resolve enemies

    SDL_UpdateWindowSurface( window );
    check_keyboard();
}
