#include <memory>
#define OLC_PGE_APPLICATION

#include "Menu.hpp"

int main() {
  StateContext c(std::make_unique<Menu>());
  if (c.Load()) {
    c.Start();
  }
  return 0;
}