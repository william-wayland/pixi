#include "Context.hpp"

StateContext::StateContext()
    : m_state(nullptr), m_upcoming_state(nullptr), m_running(true) {
  sAppName = "Pixi Game Engine";
}

bool StateContext::Load() {
  return Construct(SCREEN_WIDTH, SCREEN_HEIGHT, 2, 2, false, true, false);
}

void StateContext::TransitionTo(std::unique_ptr<State> state) {
  m_upcoming_state = std::move(state);
}

void StateContext::Quit() { m_running = false; }

bool StateContext::OnUserCreate() { return true; }
bool StateContext::OnUserUpdate(float fElapsedTime) {
  if (!m_running) {
    return false;
  }

  if (m_state) {
    m_state->Tick(fElapsedTime);
    m_state->Render();
  }

  if (m_upcoming_state != nullptr) {
    m_state = std::move(m_upcoming_state);
    m_state->SetContext(this);
    m_upcoming_state = nullptr;
  }

  return true;
}