#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include <stdio.h>
#include "Controls.h"
#include "Input.h"
#include "Constants.h"
#include "Map_Manager.h"
#include "Dot.h"
#include "AnimationManager.h"
//#include "Texture_Manager.h"

class Game
{
public:
	static Game* create_game();

	void run();

	~Game();
private:
	Input _input;
	Map_Manager* _map_manager;

	//The dot that will be moving around on the screen
	Dot* _dot;

	bool _is_running;
	Game();


	bool init();

	void tick(int dt);

	void game_tick(int dt);
	void exit();
};

#endif