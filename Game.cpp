#include "Game.hpp"

Game::Game()
{
	sAppName = "Pixi Game Engine";
}


bool Game::Load()
{
	Construct(256, 512, 2, 2);

	space[2][3] = true;

	return true;
}

bool Game::OnUserCreate()
{
	return true;
}

bool Game::OnUserUpdate(float fElapsedTime)
{
	for (int y = 0; y < space.size(); y++) {
		for(int x = 0; x < space[y].size(); x++) {
			auto colour = space[y][x] ? olc::WHITE : olc::BLACK;
			DrawRect(x * B_HEIGHT, y * B_WIDTH, B_HEIGHT, B_WIDTH, colour);
		}
	}
	return true;
}
