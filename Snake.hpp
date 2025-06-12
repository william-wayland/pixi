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
  int To1D(olc::vi2d in);
  olc::vi2d To2D(int in);
  olc ::vi2d RandomLocation();
  olc ::vi2d RandomLocationNotOnSnake();
  void WrapPosition(olc::vi2d *pos);

  Timestamp m_last_tick;
  TimeDuration m_tick_rate;

  constexpr static size_t N_ROW = 15;
  constexpr static size_t N_COLUMN = 7;
  constexpr static size_t B_WIDTH = StateContext::SCREEN_WIDTH / N_COLUMN;
  constexpr static size_t B_HEIGHT = StateContext::SCREEN_HEIGHT / N_ROW;
  const olc::vi2d B_DIMENSION = {B_WIDTH, B_HEIGHT};

  bool m_game_over;
  olc::vi2d m_v;
  olc::vi2d m_new_v;
  std::deque<olc::vi2d> m_snake;
  olc ::vi2d m_treat;
};
