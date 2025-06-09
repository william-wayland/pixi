#include "Snake.hpp"
#include "Menu.hpp"

void Snake::Tick(float dt) {
  if (Timestamp::Now() - m_last_tick > m_tick_rate) {
    GameTick();
    m_last_tick = Timestamp::Now();
  }

  if (Context()->GetKey(olc::ESCAPE).bPressed) {
    Context()->TransitionTo(std::make_unique<Menu>());
    return;
  }
}

void Snake::Render() {
  // Background
  Context()->FillRect(0, 0, Context()->ScreenWidth(), Context()->ScreenHeight(),
                      olc::BLACK);

  // World

  // Treat

  // Snake
  for (const auto &p : m_snake) {
    Context()->FillRect(p.x * B_WIDTH, p.y * B_HEIGHT, B_HEIGHT, B_WIDTH,
                        olc::WHITE);
  }
}

void Snake::Reset() {

  m_snake = {{7, 7}};
  m_v = {0, 0};
};

void Snake::GameTick() {}
