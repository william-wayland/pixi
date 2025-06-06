#pragma once

#include "olcPixelGameEngine.h"
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
  StateContext(std::unique_ptr<State> state) : m_state(nullptr) {
    sAppName = "Pixi Game Engine";
    TransitionTo(std::move(state));
  }

  bool Load() {
    return Construct(SCREEN_WIDTH, SCREEN_HEIGHT, 2, 2, false, true);
  }

  void TransitionTo(std::unique_ptr<State> state) {
    if (state == nullptr)
      return;
    m_state = std::move(state);
    m_state->SetContext(this);
  }

  bool OnUserCreate() override { return true; }
  bool OnUserUpdate(float fElapsedTime) override {
    if (m_state) {
      m_state->Tick(fElapsedTime);
      m_state->Render();
    }
    return true;
  }

  constexpr static auto SCREEN_WIDTH = 245;
  constexpr static auto SCREEN_HEIGHT = 525;

private:
  std::unique_ptr<State> m_state;
};