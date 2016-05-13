#include <SDL2/SDL.h>
#include <iostream>
#include <string>

#include "projectile.h"

using namespace std;

Projectile::Projectile() {
  this->pos_x = -1000.0f;
  this->pos_y = -1000.0f;
}
void Projectile::SetOwner(ProjectileOwner ownr) {
  this->owner = ownr;
}

void Projectile::Resolve() {
  if (this->CannotBeResolved())
    return;

    if(!this->IsOnScreen()) {
      this->Deactivate();
    }
  GameEntity::Resolve();
}
