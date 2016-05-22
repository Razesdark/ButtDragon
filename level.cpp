#include <iostream>
#include <string>
#include <vector>
#include <SDL2/SDL.h>



#ifndef GAME_ENTITY
  #include "game_entity.h"
#endif

#include "game.h"
#include "stars.h"
#include "enemy.h"
#include "player.h"
#include "level.h"

Level::Level(SDL_Window *window, SDL_Surface *screen, int enemies) {
  this->is_running = true;
  this->shut_down = false;
  this->screen_surface = screen;
  this->window = window;
  this->enemies_on_screen = enemies;
  this->active_enemies = enemies;
  this->stars_on_screen = 20;
}

void Level::InitializeAssets() {

  // Initialize Background assets
  this->stars.reserve(this->stars_on_screen);
  for(int i = 0; i < this->stars_on_screen; i++) {
    this->stars.push_back(Star());
    this->stars[i].PostInitialize(this->screen_surface);
  }

  this->enemies.reserve(this->enemies_on_screen);
  for(int i = 0; i < this->enemies_on_screen; i++) {
    this->enemies.push_back(Enemy());
    this->enemies[i].PostInitialize(this->screen_surface);
  }

  this->player = new Player();
  this->player->SetWindow(this->screen_surface);
  this->player->SetSprite("assets/spacedragon1.bmp", true);
  this->player->Activate();
  this->player->pos_x = 0;
  this->player->pos_y = 0;

}

void Level::GameTick() {
  // Blank the entire screen
  SDL_FillRect( this->screen_surface, NULL, SDL_MapRGB( this->screen_surface->format, 0x12, 0x12, 0x13 ) ); // Sets Background color, #121213

  // Resolve Background assets first
  for(int i = 0; i < this->stars_on_screen; i++)
    stars[i].Resolve();

  // Resolve enemies
  for(int i = 0; i < this->enemies_on_screen; i++){
    this->enemies[i].Resolve();
    if (player->CheckOffensiveCollision((Enemy *)&enemies[i]) == true) {
      this->active_enemies -= 1;
      enemies[i].Deactivate();
    }
    // if (player->CheckDefensiveCollision((Enemy *)&enemies[i]) == true) {
    //   this->is_running = false;
    // }
  }


  // Resolves player and players projectiles
  player->Resolve();


  // Draw to screen
  SDL_UpdateWindowSurface( window );
  this->CheckKeyboard();
  if(this->active_enemies <= 0) {
    this->is_running = false;
  }
}

void Level::EndLevel() {

}


void Level::CheckKeyboard() {
  SDL_Event e;
  // Allow loop to quit when SDL sends Quit event
  while( SDL_PollEvent( &e ) != 0) {
    switch(e.type) {
      case SDL_QUIT:
        printf("QUITTING\r\n");
        this->is_running = false;
        this->shut_down = true;
      case SDL_KEYDOWN:
      case SDL_KEYUP:
        this->player->KeyboardEvent( &e.key );
      default:
        break;
    }
  }
}
