#include <memory>
#define OLC_PGE_APPLICATION

#include "Menu.hpp"

class Example
    : public olc::PixelGameEngine // Note olc::PixelGameEngine is inherited from
{
public:
  Example() {
    sAppName = "Example"; // You can name your application here
  }

public:
  bool OnUserCreate() override {
    // Called once at the start, so create things here
    return true;
  }

  bool OnUserUpdate(float fElapsedTime) override {
    time += fElapsedTime;
    if (time > 10) {
      SetScreenSize(100, 100);
    }

    DrawCircle({40, 40}, 3);
    // called once per frame
    return true;
  }

  float time = 0;
};

int main() {
  StateContext c{};
  if (c.Load()) {
    c.TransitionTo(std::make_unique<Menu>());
    c.Start();
  }
  // Example demo;
  // if (demo.Construct(256, 240, 4, 4))
  //   demo.Start();

  return 0;
}