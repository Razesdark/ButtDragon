#include <SDL2/SDL.h>
#include <string>

#ifndef GAME_ENTITY
  #include "game_entity.h"
#endif

#define STARS 1

#define STARS_ON_SCREEN 20

class Star : public GameEntity {
  public:
    Star();
    void PostInitialize(SDL_Surface*);
    void Resolve();
};
