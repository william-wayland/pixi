#pragma once

#include "Context.hpp"
#include "Snake.hpp"
#include "Stacker.hpp"
#include <memory>
#include <utility>

class Menu : public State {
public:
  Menu() {}

protected:
  using Factory = std::function<std::unique_ptr<State>()>;
  using NamedFactory = std::pair<std::string, Factory>;
  using Games = std::array<NamedFactory, 2>;

  Games games = {
      {{"Stacker", MakeState<Stacker>}, {"Snake", MakeState<Snake>}},
  };

  int selection = 0;
  size_t Selection() { return selection % games.size(); }

  virtual void Tick(float dt) override {
    if (Context()->GetKey(olc::DOWN).bPressed) {
      selection += 1;
    }

    if (Context()->GetKey(olc::UP).bPressed) {
      selection -= 1;
    }

    if (Context()->GetKey(olc::ENTER).bPressed) {
      const auto &[game, factory] = games[Selection()];

      std::cout << "Playing: " << game << std::endl;
      Context()->TransitionTo(factory());
      return;
    }

    if (Context()->GetKey(olc::ESCAPE).bPressed) {
      Context()->Quit();
    }
  }
  virtual void Render() override {
    Context()->FillRect(0, 0, Context()->ScreenWidth(),
                        Context()->ScreenHeight(), olc::WHITE);

    int i = 0;
    for (const auto &[game, _] : games) {
      auto s = Context()->GetTextSizeProp(game);

      if (Selection() == i) {
        Context()->DrawString({10, i * s.y + 20}, ">", olc::BLACK);
      }
      Context()->DrawString({20, i * s.y + 20}, game, olc::BLACK);
      i++;
    }
  };
};