#include "Game.hpp"

Game::Game()
{
	sAppName = "Pixi Game Engine";
}


bool Game::OnUserCreate()
{
	return true;
}

bool Game::OnUserUpdate(float fElapsedTime)
{
	for (int x = 0; x < ScreenWidth(); x++) {
		for (int y = 0; y < ScreenHeight(); y++) {
			Draw(x, y, olc::Pixel(rand() % 255, rand() % 255, rand() % 255));
		}		
	}
	return true;
}
