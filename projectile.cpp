#include <SDL2/SDL.h>
#include <iostream>
#include <string>

#include "projectile.h"

using namespace std;

Projectile::Projectile() {

}
void Projectile::SetOwner(ProjectileOwner ownr) {
  this->owner = ownr;
}

void Projectile::Resolve() {

  if (this->_window == NULL || this->_sprite == NULL || this->active != true)
    return;
    if(!this->IsOnScreen()) {
      cout << "Deactivating Projectile" << endl;
      this->Deactivate();
    }
  GameEntity::Resolve();
} 
