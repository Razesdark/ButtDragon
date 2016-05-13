#include <SDL2/SDL.h>
#include <iostream>
#include <string>

#include "game.h"

const int SCREEN_HEIGHT = 640;
const int SCREEN_WIDTH = 480;

int initialize_game(int, int);
void run_game();
void end_game();


int main() {
   initialize_game(SCREEN_WIDTH, SCREEN_HEIGHT);
   initialize_assets();
   run_game();
   end_game();
}
