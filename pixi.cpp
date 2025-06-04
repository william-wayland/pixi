#define OLC_PGE_APPLICATION

#include "Game.hpp"

int main() {
  Game game;
  if (game.Load()) {
    game.Start();
  }
  return 0;
}