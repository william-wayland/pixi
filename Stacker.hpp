#pragma once

#include "Context.hpp"
#include "Time.hpp"

class Stacker : public State {
public:
  Stacker() { Reset(); }

protected:
  virtual void Tick(float dt) override;
  virtual void Render() override;

private:
  void Reset();
  void GameTick();

  Timestamp m_last_tick;
  TimeDuration m_tick_rate;

  constexpr static auto N_ROW = 15;
  constexpr static auto N_COLUMN = 7;
  constexpr static auto B_WIDTH = StateContext::SCREEN_WIDTH / N_COLUMN;
  constexpr static auto B_HEIGHT = StateContext::SCREEN_HEIGHT / N_ROW;

  std::array<std::array<bool, N_COLUMN>, N_ROW> m_space;
  int m_x, m_y; // position of left most block
  int m_size;   // size of block
  int m_xv;     // velocity of block (left or right)
};