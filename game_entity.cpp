#include <SDL2/SDL.h>
#include <iostream>
#include <string>
#include <typeinfo>
#include "game_entity.h"

#define quote(x) #x

using namespace std;

GameEntity::GameEntity() {
  this->pos_x = 0;
  this->pos_y = 0;
  this->vector_x = 0;
  this->vector_y = 0;
  this->_window = NULL;
  this->_sprite = NULL;
  this->active = false;
}

void GameEntity::SetWindow(SDL_Surface *window) {
  this->_window = window;
}
void GameEntity::SetSprite(std::string path, bool alpha) {
  this->_sprite = SDL_LoadBMP( path.c_str() );
  if(alpha == true) {
    SDL_SetColorKey(  this->_sprite,
                      SDL_TRUE,
                      SDL_MapRGB( this->_sprite->format, 0xFF, 0x00, 0xFF ) // COLOR: Magenta #FF00FF
                    );
  }
}
bool GameEntity::IsOnScreen(void) {
    if(this->pos_x < 0 - this->_sprite->w)
      return false;
    if(this->pos_y < 0 - this->_sprite->h)
      return false;
    if(this->pos_x > this->_window->w)
      return false;
    if(this->pos_y > this->_window->h)
      return false;

    return true;
}

inline bool GameEntity::CannotBeResolved() {
  return (this->_window == NULL || this->_sprite == NULL || this->active != true);
}

void GameEntity::Resolve(void) {
  // -----------------------------------------------------
  //    Update the current object and draw it on screen
  // ------------------------------------------------------
  if (this->CannotBeResolved())
    return;

  this->pos_x += this->vector_x;
  this->pos_y += this->vector_y;

  SDL_Rect position_rect;
  position_rect.x = (int)this->pos_x;
  position_rect.y = (int)this->pos_y;

  SDL_BlitSurface( this->_sprite, NULL, this->_window, &position_rect);
}

void GameEntity::Activate() {
  this->active = true;
}
void GameEntity::Deactivate() {
  cout << "DEACTIVATE";
  cout << quote(this) << endl;
  this->active = false;
}
bool GameEntity::IsActive() {
  return this->active;
}
