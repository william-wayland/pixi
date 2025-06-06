#include "Stacker.hpp"
#include "Menu.hpp"

void Stacker::Tick(float dt) {
  if (Context()->GetKey(olc::SPACE).bPressed) {
    int next_size = 0;

    for (int i = 0; i < m_size; ++i) {
      if (m_y == N_ROW - 1 || m_space[m_y + 1][m_x + i]) {
        m_space[m_y][m_x + i] = true;
        next_size += 1;
      }
    }

    m_size = next_size;
    m_y -= 1;
    m_tick_rate = (m_tick_rate * 94) / 100;
  }

  if (Context()->GetKey(olc::ESCAPE).bPressed) {
    Context()->TransitionTo(std::make_unique<Menu>());
    return;
  }

  if (Context()->GetKey(olc::R).bPressed) {
    Reset();
  }

  if (Timestamp::Now() - m_last_tick > m_tick_rate) {
    GameTick();
    m_last_tick = Timestamp::Now();
  }
}

void Stacker::Render() {
  Context()->FillRect(0, 0, Context()->ScreenWidth(), Context()->ScreenHeight(),
                      olc::BLACK);

  // Previous rows
  for (int y = 0; y < m_space.size(); y++) {
    for (int x = 0; x < m_space[y].size(); x++) {
      if (m_space[y][x])
        Context()->FillRect(x * B_WIDTH, y * B_HEIGHT, B_HEIGHT, B_WIDTH,
                            olc::BLUE);
    }
  }

  // Player
  for (int i = 0; i < m_size; ++i) {
    Context()->FillRect((m_x + i) * B_WIDTH, m_y * B_HEIGHT, B_HEIGHT, B_WIDTH,
                        olc::WHITE);
  }

  // Grid
  for (int y = 0; y < m_space.size(); y++) {
    for (int x = 0; x < m_space[y].size(); x++) {
      Context()->DrawRect(x * B_WIDTH, y * B_HEIGHT, B_WIDTH - 1, B_HEIGHT - 1,
                          olc::GREY);
    }
  }
}

void Stacker::Reset() {
  m_space = {};
  m_last_tick = Timestamp::Now() - 1s;
  m_x = 2;
  m_y = N_ROW - 1;
  m_size = 3;
  m_xv = 1;
  m_tick_rate = 0.2s;
}

void Stacker::GameTick() {
  if (m_x <= 0 || m_x + m_size > N_COLUMN - 1) {
    m_xv *= -1;
  }

  m_x += m_xv;
}