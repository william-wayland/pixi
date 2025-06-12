#include "Snake.hpp"
#include "Context.hpp"
#include "Menu.hpp"

#include <random>
#include <vector>

const static olc::vi2d ZERO = {0, 0};
const static olc::vi2d LEFT = {-1, 0};
const static olc::vi2d RIGHT = {1, 0};
const static olc::vi2d UP = {0, -1};
const static olc::vi2d DOWN = {0, 1};

void Snake::Tick(float dt) {
  if (Timestamp::Now() - m_last_tick > m_tick_rate) {
    GameTick();
    m_last_tick = Timestamp::Now();
  }

  if (Context()->GetKey(olc::ESCAPE).bPressed) {
    Context()->TransitionTo(std::make_unique<Menu>());
  }

  if (Context()->GetKey(olc::R).bPressed) {
    Reset();
  }

  if (Context()->GetKey(olc::LEFT).bPressed)
    m_new_v = LEFT;
  if (Context()->GetKey(olc::RIGHT).bPressed)
    m_new_v = RIGHT;
  if (Context()->GetKey(olc::UP).bPressed)
    m_new_v = UP;
  if (Context()->GetKey(olc::DOWN).bPressed)
    m_new_v = DOWN;
}

olc::vf2d DirectionToHeadOffset(olc::vi2d dir) {
  if (dir == LEFT) {
    return olc::vf2d{1, 0.5};
  }
  if (dir == RIGHT) {
    return olc::vf2d{0, 0.5};
  }
  if (dir == UP) {
    return olc::vf2d{0.5, 1};
  }
  if (dir == DOWN) {
    return olc::vf2d{0.5, 0};
  }
  return ZERO;
}

void Snake::Render() {
  // Background
  Context()->FillRect(0, 0, Context()->ScreenWidth(), Context()->ScreenHeight(),
                      olc::BLACK);

  auto head_origin =
      m_snake[0] * B_DIMENSION + DirectionToHeadOffset(m_v) * B_DIMENSION;
  Context()->FillCircle(head_origin, B_WIDTH / 2);

  // Snake Body
  for (auto s = m_snake.begin() + 1; s < m_snake.end(); s++) {
    Context()->FillRect((*s) * B_DIMENSION, B_DIMENSION, olc::WHITE);
  }
  // Treat
  Context()->FillRect(m_treat * B_DIMENSION, B_DIMENSION, olc::GREEN);
}

void Snake::Reset() {
  m_game_over = false;
  m_snake = {{2, 4}, {2, 3}, {2, 2}};
  m_v = DOWN;
  m_new_v = ZERO;
  m_tick_rate = 0.2s;
  m_treat = RandomLocationNotOnSnake();
};

void Snake::GameTick() {
  if (m_game_over) {
    return;
  }

  // if there's a new velocity and it isn't in the opposite direction
  if (m_new_v != ZERO && m_new_v + m_v != ZERO) {
    m_v = m_new_v;
  }
  m_new_v = ZERO;

  // preemptive snake head
  olc::vi2d head = m_snake[0] + m_v;
  WrapPosition(&head);

  // Check for consumption
  if (head == m_treat) {
    m_snake.push_front(head);

    if (m_snake.size() == N_ROW * N_COLUMN) {
      m_game_over = true;
    } else {
      m_treat = RandomLocationNotOnSnake();
    }

    return;
  }

  // Move body (while checking for head collisions)
  for (auto i = m_snake.rbegin(); i < m_snake.rend() - 1; i++) {
    *i = *(i + 1);
    if (head == *(i)) {
      m_game_over = true;
    }
  }

  // Finally move the snakes head and wrap around world
  m_snake[0] = head;
  WrapPosition(&m_snake[0]);
}

int Snake::To1D(olc::vi2d in) { return in.x + in.y * N_COLUMN; }
olc::vi2d Snake::To2D(int in) {
  return {static_cast<int32_t>(in % N_COLUMN),
          static_cast<int32_t>(in / N_COLUMN)};
}

olc::vi2d Snake::RandomLocation() {
  static std::random_device dev;
  static std::uniform_int_distribution<int32_t> rx(0, N_COLUMN - 1);
  static std::uniform_int_distribution<int32_t> ry(0, N_ROW - 1);
  return {rx(dev), ry(dev)};
}

olc::vi2d Snake::RandomLocationNotOnSnake() {
  static std::random_device dev;

  const size_t remaining = (N_ROW * N_COLUMN) - m_snake.size();
  std::uniform_int_distribution<size_t> dist(0, remaining);
  const size_t index = dist(dev);

  std::vector<bool> space(N_ROW * N_COLUMN, false);
  for (const auto &part : m_snake) {
    space[To1D(part)] = true;
  }

  for (int i = 0, counter = 0; i < space.size(); ++i) {
    if (space[i]) {
      continue;
    }
    if (counter == index) {
      return To2D(i);
    }
    ++counter;
  }

  // Shouldn't happen...
  std::cout << "Random algorithm failed. Fallback to random position..."
            << std::endl;
  return RandomLocation();
}

void Snake::WrapPosition(olc::vi2d *pos) {
  pos->x = (N_COLUMN + pos->x) % N_COLUMN;
  pos->y = (N_ROW + pos->y) % N_ROW;
}