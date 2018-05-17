//Using SDL and standard IO
#include <SDL.h>
#include <stdio.h>
#include "Constants.h"
#include "Game.cpp"


int main(int argc, char* args[])
{
	Game game = Game::create_game();
	game.run();
	return 0;
}