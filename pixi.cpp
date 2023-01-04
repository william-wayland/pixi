#define OLC_PGE_APPLICATION

#include "Game.hpp"

int main()
{
	Game game;
	if (game.Construct(256, 240, 4, 4))
		game.Start();

	return 0;
}