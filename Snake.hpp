#pragma once

#include "Context.hpp"
#include "Time.hpp"

class Snake : public State {
public:
  Snake() { Reset(); }

protected:
  virtual void Tick(float dt) override;
  virtual void Render() override;

private:
  void Reset();
  void GameTick();

  Timestamp m_last_tick;
  TimeDuration m_tick_rate;

  constexpr static auto SCREEN_WIDTH = 500;
  constexpr static auto SCREEN_HEIGHT = 500;
  constexpr static auto N_ROW = 15;
  constexpr static auto N_COLUMN = 15;
  constexpr static auto B_WIDTH = SCREEN_WIDTH / N_COLUMN;
  constexpr static auto B_HEIGHT = SCREEN_HEIGHT / N_ROW;

  std::array<std::array<bool, N_COLUMN>, N_ROW> m_space;
  olc::vi2d m_v;
  std::vector<olc::vi2d> m_snake;
};