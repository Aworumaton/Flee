#pragma once
#include "Game.h"


int main(int argc, char* args[])
{
	Game* game = Game::create_game();
	game->run();

	delete(game);

	return 0;
}