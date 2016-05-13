#include <SDL2/SDL.h>
#include <string>

#include "enemy.h"

#ifndef GAME_ENTITY
  #include "game_entity.h"
#endif

#ifndef PROJECTILE
  #include "projectile.h"
#endif

#define MAX_SHOTS_FOR_PLAYER 5

class Player : public GameEntity {
  public:
    Player();
    void Resolve(void);
    void KeyboardEvent(SDL_KeyboardEvent*);
    void SetWindow(SDL_Surface*);
    void CheckOffensiveCollision(Enemy*);
    bool CheckDefensiveCollision(Enemy*);
  private:
    bool key_down, key_up, key_left, key_right, shooting;
    Projectile Shots[MAX_SHOTS_FOR_PLAYER];
    void ReadKeyboard(void);
    void Shoot(void);

};
