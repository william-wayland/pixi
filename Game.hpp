#pragma once

#include "olcPixelGameEngine.h"

#include <array>

#include "Time.h"

class Game : public olc::PixelGameEngine
{
public:
	Game();
	
	bool Load();
	bool OnUserCreate() override;
	bool OnUserUpdate(float fElapsedTime) override;

private:
	void Tick();
	void Render();

	constexpr static auto SCREEN_WIDTH = 245;
	constexpr static auto SCREEN_HEIGHT = 525;
	constexpr static auto N_ROW = 15;
	constexpr static auto N_COLUMN = 7;
	constexpr static auto B_WIDTH = SCREEN_WIDTH / N_COLUMN;
	constexpr static auto B_HEIGHT = SCREEN_HEIGHT / N_ROW;

	std::array<std::array<bool, N_COLUMN>, N_ROW> m_space;
	Timestamp m_last_tick;
	int m_x, m_y; // position of left most block
	int m_size; // size of block
	int m_xv;
	TimeDuration m_tick_rate;
};
