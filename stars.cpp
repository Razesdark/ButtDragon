#include <SDL2/SDL.h>
#include <iostream>
#include <stdlib.h>
#include <string>

#include "stars.h"

using namespace std;

Star::Star() {
  this->SetSprite("assets/star.bmp", true);
}

void Star::PostInitialize(SDL_Surface *window) {
  this->SetWindow(window);
  this->pos_y = rand() % this->_window->h;
  this->pos_x = rand() % this->_window->w;
  this->vector_x = ((static_cast <float> (rand()) / static_cast <float> (RAND_MAX)) * -1) * 0.4f;
  this->Activate();
}

void Star::Resolve(){
  if(!this->IsOnScreen()) {
    this->pos_x = this->_window->w - 1;
  }

  GameEntity::Resolve();
}
