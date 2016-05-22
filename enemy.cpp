#include <SDL2/SDL.h>
#include <iostream>
#include <string>
#include <stdlib.h>

#include "enemy.h"

using namespace std;

Enemy::Enemy() {
  cout << "RAWR" << endl;
  this->SetSprite("./assets/enemy.bmp", true);
  this->last_shot_tick = 0;

}
void Enemy::Shoot() {
  for(int i = 0; i < MAX_SHOTS_FOR_ENEMY; i++) {
      Uint32 current_tick = SDL_GetTicks();
     if(!this->Shots[i].IsActive() && current_tick - this->last_shot_tick > rand() % (Uint32)1500000) {
      this->last_shot_tick = current_tick;
      this->Shots[i].pos_x = this->pos_x;
       this->Shots[i].pos_y = this->pos_y + (this->_sprite->h / 2) - (this->Shots[i]._sprite->h/2);
       this->Shots[i].vector_x = this->vector_x + - 0.05f;
       this->Shots[i].vector_y = 0.0f;
       if(this->Shots[i].IsOnScreen())
          this->Shots[i].Activate();
     }
  }
}
void Enemy::PostInitialize(SDL_Surface *window) {
  this->SetWindow(window);
  this->pos_y = rand() % this->_window->h - this->_sprite->h + 1;
  this->pos_x = ((this->_window->w/2) + (rand() % this->_window->w / 2)) - (this->_sprite->w);
  this->vector_x = ((static_cast <float> (rand()) / static_cast <float> (RAND_MAX)) * -1) * 0.01f;
  this->vector_y = ((static_cast <float> (rand()) / static_cast <float> (RAND_MAX)) * -1) * 0.01f;
  this->Activate();

  for(int i = 0; i < MAX_SHOTS_FOR_ENEMY; i++) {
     this->Shots[i].SetSprite("./assets/enemy_projectile.bmp", true);
     this->Shots[i].SetWindow(window);
     this->Shots[i].Deactivate();
  }

}

void Enemy::Resolve() {
  for(int i = 0; i < MAX_SHOTS_FOR_ENEMY; i++) {
    this->Shots[i].Resolve();

  if(this->_window == NULL || this->_sprite == NULL || this->active != true)
    return;

  this->Shoot();
  if(!this->IsOnScreen()) {
    this->pos_y = rand() % this->_window->h - this->_sprite->h - 1;
    this->pos_x = (this->_window->w) - (this->_sprite->w) - 1;
    this->vector_x = ((static_cast <float> (rand()) / static_cast <float> (RAND_MAX)) * -1) * 0.1f;
    this->vector_y = ((static_cast <float> (rand()) / static_cast <float> (RAND_MAX)) * -1) * 0.1f;
  }

  }
  GameEntity::Resolve();
}
