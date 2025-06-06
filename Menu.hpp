#pragma once

#include "Context.hpp"
#include "Stacker.hpp"

class Menu : public State {
public:
  Menu() {}

protected:
  virtual void Tick(float dt) override {
    if (Context()->GetKey(olc::ENTER).bPressed) {
      Context()->TransitionTo(std::make_unique<Stacker>());
    }
  }
  virtual void Render() override {
    Context()->FillRect(0, 0, Context()->ScreenWidth(),
                        Context()->ScreenHeight(), olc::WHITE);
  };
};