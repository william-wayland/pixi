#pragma once

#include "olcPixelGameEngine.h"

#include <array>

class Game : public olc::PixelGameEngine
{
public:
	Game();
	
	bool Load();
	bool OnUserCreate() override;
	bool OnUserUpdate(float fElapsedTime) override;

private:
	constexpr static auto SCREEN_WIDTH = 256;
	constexpr static auto SCREEN_HEIGHT = 512;
	constexpr static auto N_ROW = 20;
	constexpr static auto N_COLUMN = 10;
	constexpr static auto B_WIDTH = SCREEN_WIDTH / N_COLUMN;
	constexpr static auto B_HEIGHT = SCREEN_HEIGHT / N_ROW;


	std::array<std::array<bool, N_COLUMN>, N_ROW> space;
};
