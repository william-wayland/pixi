#pragma once

#include "olcPixelGameEngine.h"
#include <cstddef>
#include <cstdlib>
#include <memory>

class StateContext;

class State {
public:
  virtual ~State() {}

  void SetContext(StateContext *context) {
    this->m_context = std::move(context);
  }
  StateContext *Context() { return m_context; }

  virtual void Tick(float dt) = 0;
  virtual void Render() = 0;

protected:
  StateContext *m_context;
};

class StateContext : public olc::PixelGameEngine {
public:
  StateContext();

  bool Load();

  void TransitionTo(std::unique_ptr<State> state);

  void Quit();

  constexpr static auto SCREEN_WIDTH = 245;
  constexpr static auto SCREEN_HEIGHT = 525;

protected:
  bool OnUserCreate() override;
  bool OnUserUpdate(float fElapsedTime) override;

  std::unique_ptr<State> m_state;
  std::unique_ptr<State> m_upcoming_state;
  bool m_running;
};

template <typename T> std::unique_ptr<State> MakeState() {
  return std::make_unique<T>();
}