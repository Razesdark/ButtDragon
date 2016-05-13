#include <SDL2/SDL.h>
#include <string>

#define PROJECTILE 1

#ifndef GAME_ENTITY
  #include "game_entity.h"
#endif
#include "projectile.h"

#define MAX_SHOTS_FOR_ENEMY 2
#define ENEMIES_ON_SCREEN 2

class Enemy : public GameEntity {
  private:
    int ticks;
    Uint32 last_shot_tick;
  public:
    Projectile Shots[MAX_SHOTS_FOR_ENEMY];
    Enemy();
    void Resolve();
    void PostInitialize(SDL_Surface*);
    void Shoot();
};
