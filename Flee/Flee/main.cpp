/*
*	Author: Omer Sari
*/
#pragma once
#include "Game.h"


int main(int argc, char* args[])
{
	Game* game = Game::CreateGame();
	game->Run();

	delete(game);

	return 0;
}