#include <SDL2/SDL.h>
#include <string>

#define PROJECTILE 1

#ifndef GAME_ENTITY
  #include "game_entity.h"
#endif

enum ProjectileOwner {
  OWNER_PLAYER,
  OWNER_ENEMY
};

class Projectile : public GameEntity {
  public:
    ProjectileOwner owner;
    Projectile();
    void Resolve();
    void SetOwner(ProjectileOwner);
};
