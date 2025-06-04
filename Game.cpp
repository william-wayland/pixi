#include "Game.hpp"

using namespace std::literals;

Game::Game()
    : m_space(), m_last_tick(Timestamp::Now() - 1s), m_x(2), m_y(N_ROW - 1),
      m_size(3), m_xv(1), m_tick_rate(0.2s) {
  sAppName = "Pixi Game Engine";
  Reset();
}

bool Game::Load() {
  return Construct(SCREEN_WIDTH, SCREEN_HEIGHT, 2, 2, false, true);
}

bool Game::OnUserCreate() { return true; }

bool Game::OnUserUpdate(float fElapsedTime) {
  if (GetKey(olc::SPACE).bPressed) {
    int next_size = 0;

    for (int i = 0; i < m_size; ++i) {
      if (m_y == N_ROW - 1 || m_space[m_y + 1][m_x + i]) {
        m_space[m_y][m_x + i] = true;
        next_size += 1;
      }
    }

    m_size = next_size;
    m_y -= 1;
    m_tick_rate = static_cast<double>(m_tick_rate) * 0.94;
  }

  if (GetKey(olc::R).bPressed) {
    Reset();
  }

  // Game Tick
  if (Timestamp::Now() - m_last_tick > m_tick_rate) {
    Tick();
    m_last_tick = Timestamp::Now();
  }

  Render();
  return true;
}

void Game::Tick() {
  if (m_x <= 0 || m_x + m_size > N_COLUMN - 1) {
    m_xv *= -1;
  }

  m_x += m_xv;
}

void Game::Render() {
  FillRect(0, 0, ScreenWidth(), ScreenHeight(), olc::BLACK);

  // Previous rows
  for (int y = 0; y < m_space.size(); y++) {
    for (int x = 0; x < m_space[y].size(); x++) {
      if (m_space[y][x])
        FillRect(x * B_WIDTH, y * B_HEIGHT, B_HEIGHT, B_WIDTH, olc::BLUE);
    }
  }

  // Player
  for (int i = 0; i < m_size; ++i) {
    FillRect((m_x + i) * B_WIDTH, m_y * B_HEIGHT, B_HEIGHT, B_WIDTH,
             olc::WHITE);
  }

  // Grid
  for (int y = 0; y < m_space.size(); y++) {
    for (int x = 0; x < m_space[y].size(); x++) {
      DrawRect(x * B_WIDTH, y * B_HEIGHT, B_WIDTH - 1, B_HEIGHT - 1, olc::GREY);
    }
  }
}

void Game::Reset() {
  m_space = {};
  m_last_tick = Timestamp::Now() - 1s;
  m_x = 2;
  m_y = N_ROW - 1;
  m_size = 3;
  m_xv = 1;
  m_tick_rate = 0.2s;
}
