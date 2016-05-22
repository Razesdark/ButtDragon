#include <iostream>
#include <string>
#include <SDL2/SDL.h>

#ifndef GAME_ENTITY
#include "game_entity.h"
#endif

#include "game.h"
#include "stars.h"
#include "enemy.h"
#include "player.h"


using namespace std;

bool game_running = true;


SDL_Event e;

Player* player;
Star stars[STARS_ON_SCREEN];
Enemy enemies[ENEMIES_ON_SCREEN];

void inline game_loop();

void initialize_assets() {
  player = new Player();
  player->SetWindow(screenSurface);
  player->SetSprite("assets/spacedragon1.bmp", true);
  player->Activate();
  player->pos_x = 0;
  player->pos_y = 0;


  // Initialize Background assets
  for(int i = 0; i < STARS_ON_SCREEN; i++) {
    stars[i].PostInitialize(screenSurface);
  }

  for(int i = 0; i < ENEMIES_ON_SCREEN; i++) {
    enemies[i].PostInitialize(screenSurface);
  }

}

void run_game() {
  while(game_running) {
    game_loop();
  }
}
void end_game() {
  free(player);
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

    // Resolve enemies
    for(int i = 0; i < ENEMIES_ON_SCREEN; i++){
      enemies[i].Resolve();
      player->CheckOffensiveCollision((Enemy *)&enemies[i]);
      if (player->CheckDefensiveCollision((Enemy *)&enemies[i]) == true) {
        game_running = false;
      }
    }


    // Resolves player and players projectiles
    player->Resolve();


    // Draw to screen
    SDL_UpdateWindowSurface( window );
    check_keyboard();
}
