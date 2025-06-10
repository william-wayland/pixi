#include "Snake.hpp"
#include "Context.hpp"
#include "Menu.hpp"

#include <random>

void Snake::Tick(float dt) {
  if (Timestamp::Now() - m_last_tick > m_tick_rate) {
    GameTick();
    m_last_tick = Timestamp::Now();
  }

  if (Context()->GetKey(olc::ESCAPE).bPressed) {
    Context()->TransitionTo(std::make_unique<Menu>());
  }

  if (Context()->GetKey(olc::LEFT).bPressed)
    m_v = {-1, 0};
  if (Context()->GetKey(olc::RIGHT).bPressed)
    m_v = {1, 0};
  if (Context()->GetKey(olc::UP).bPressed)
    m_v = {0, -1};
  if (Context()->GetKey(olc::DOWN).bPressed)
    m_v = {0, 1};
}

void Snake::Render() {
  // Background
  Context()->FillRect(0, 0, Context()->ScreenWidth(), Context()->ScreenHeight(),
                      olc::BLACK);

  // Treat
  Context()->FillRect(m_treat.x * B_WIDTH, m_treat.y * B_HEIGHT, B_HEIGHT,
                      B_WIDTH, olc::GREEN);

  // Snake
  for (const auto &p : m_snake) {
    Context()->FillRect(p.x * B_WIDTH, p.y * B_HEIGHT, B_HEIGHT, B_WIDTH,
                        olc::WHITE);
  }
}

void Snake::Reset() {
  m_game_over = false;
  m_snake = {{3, 7}};
  m_v = {0, 0};
  m_tick_rate = 0.2s;
  m_treat = RandomLocation();
};

void Snake::GameTick() {

  if (m_game_over) {
    return;
  }

  // move snake
  const auto head = m_snake[0] + m_v;

  if (head == m_treat) {
    m_treat = RandomLocation(); // todo : check if location is free of snake?
    m_snake.push_front(head);
    if (m_snake.size() == N_ROW * N_COLUMN) {
      m_game_over = true;
    }
    return;
  }

  for (auto i = m_snake.rbegin(); i < m_snake.rend() - 1; i++) {
    if (head == *(i)) {
      m_game_over = true;
    }
    *i = *(i + 1);
  }

  m_snake[0] = head;
  m_snake[0].x = (N_COLUMN + m_snake[0].x) % N_COLUMN;
  m_snake[0].y = (N_ROW + m_snake[0].y) % N_ROW;
}

olc::vi2d Snake::RandomLocation() {
  static std::random_device dev;
  static std::uniform_int_distribution<int32_t> rx(0, N_COLUMN - 1);
  static std::uniform_int_distribution<int32_t> ry(0, N_ROW - 1);
  return {rx(dev), ry(dev)};
}
