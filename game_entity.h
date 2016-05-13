#ifndef GAME_ENTITY_DEFINED
#define GAME_ENTITY_DEFINED 1
#include <SDL2/SDL.h>
#include <string>

#define GAME_ENTITY 1

class GameEntity {
  private:


  public:
    bool active;
    Uint32 last_updated_tick;

    SDL_Surface* _window;
    SDL_Surface* _sprite;

    float pos_x, pos_y;
    float vector_x, vector_y;
    GameEntity();
    void SetWindow(SDL_Surface*);
    void SetSprite(std::string, bool);
    void Resolve(void);

    inline bool CannotBeResolved();
    bool IsOnScreen();
    bool IsActive();
    void Activate();
    void Deactivate();
};
#endif
