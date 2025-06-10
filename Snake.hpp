#pragma once

#include "Context.hpp"
#include "Time.hpp"
#include <deque>

class Snake : public State {
public:
  Snake() { Reset(); }

protected:
  virtual void Tick(float dt) override;
  virtual void Render() override;

private:
  void Reset();
  void GameTick();
  olc ::vi2d RandomLocation();

  Timestamp m_last_tick;
  TimeDuration m_tick_rate;

  constexpr static auto N_ROW = 15;
  constexpr static auto N_COLUMN = 7;
  constexpr static auto B_WIDTH = StateContext::SCREEN_WIDTH / N_COLUMN;
  constexpr static auto B_HEIGHT = StateContext::SCREEN_HEIGHT / N_ROW;

  bool m_game_over;
  olc::vi2d m_v;
  std::deque<olc::vi2d> m_snake;
  olc ::vi2d m_treat;
};