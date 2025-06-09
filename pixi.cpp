#include <memory>
#define OLC_PGE_APPLICATION

#include "Menu.hpp"

int main() {
  StateContext c{};
  if (c.Load()) {
    c.TransitionTo(std::make_unique<Menu>());
    c.Start();
  }
  return 0;
}