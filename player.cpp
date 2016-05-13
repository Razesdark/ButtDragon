#include <SDL2/SDL.h>
#include <iostream>
#include <string>
#include <vector>

#include "player.h"
#ifndef PROJECTILE
  #include "projectile.h"
#endif

using namespace std;
Player::Player() {
  key_down = false;
  key_up = false;
  key_left = false;
  key_right = false;
  shooting = false;

  for(int i = 0; i < MAX_SHOTS_FOR_PLAYER; i++) {
   this->Shots[i].SetSprite("assets/projectile_player.bmp", true);
   this->Shots[i].vector_x = 0.6f;
   this->Shots[i].SetOwner( OWNER_PLAYER );
 }

}
void Player::Resolve() {
  this->ReadKeyboard();

  for(int i = 0; i < MAX_SHOTS_FOR_PLAYER; i++) {
    this->Shots[i].Resolve();
  }

  GameEntity::Resolve();
}
void Player::SetWindow(SDL_Surface* window) {
  GameEntity::SetWindow(window);
  for(int i = 0; i < MAX_SHOTS_FOR_PLAYER; i++) {
   this->Shots[i].SetWindow(window);
 }
}
void Player::KeyboardEvent(SDL_KeyboardEvent *key) {
  // printf("KEY:%d\r\n", key->keysym.scancode);
  switch(key->keysym.scancode) {
    case 82:
      this->key_up = (key->type == SDL_KEYDOWN) ? true : false;
      break;
    case 81:
      this->key_down = (key->type == SDL_KEYDOWN) ? true : false;
      break;
    case 80:
      this->key_right = (key->type == SDL_KEYDOWN) ? true : false;
      break;
    case 79:
      this->key_left = (key->type == SDL_KEYDOWN) ? true : false;
      break;
    case 44:
      if (key->type == SDL_KEYUP)
        this->shooting = false;
      if (key->type == SDL_KEYDOWN && !this->shooting) {
        this->Shoot();
        this->shooting = true;
      }
    default:
      break;
  }
}
void Player::ReadKeyboard() {
  if( this->key_down )
    this->vector_y = 0.1f;
  if( this->key_up )
    this->vector_y = -0.1f;
  if( this->key_left )
    this->vector_x = 0.1f;
  if (this->key_right )
    this->vector_x = -0.1f;

  if (!this->key_up && !this->key_down)
    this->vector_y = 0.0f;
  if (!this->key_left && !this->key_right)
    this->vector_x = 0.0f;

}

void Player::Shoot() {
  for(int i = 0; i < MAX_SHOTS_FOR_PLAYER; i++) {
    if(!this->Shots[i].IsActive()) {
      this->Shots[i].pos_x = this->pos_x + ( this->_sprite->w / 2 );
      this->Shots[i].pos_y = this->pos_y + ( this->_sprite->h / 2 );
      this->Shots[i].Activate();
      return;
    }
  }
}
