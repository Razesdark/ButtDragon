#include <SDL2/SDL.h>
#include <string>
#include <vector>

#include "enemy.h"
#ifndef STARS
#include "stars.h"
#endif
#ifndef PLAYER_DEFINED
#include "player.h"
#endif

class Level {
  public:
    bool is_running;
    bool shut_down;
    Level(SDL_Window*, SDL_Surface*, int);
    void InitializeAssets(void);
    void GameTick(void);
    void EndLevel(void);

  private:
    int enemies_on_screen, stars_on_screen;
    int active_enemies;
    std::vector<Enemy> enemies;
    std::vector<Star> stars;
    Player *player;
    SDL_Window *window;
    SDL_Surface *screen_surface;

    void CheckKeyboard(void);
};
