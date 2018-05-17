#pragma once
#include <SDL.h>
#include <stdio.h>
#include "Controls.h"
#include "Input.h"
#include "Constants.h"
//#include "Texture_Manager.h"

class Game
{
public:
	static Game* create_game();

	void run();

	~Game();
private:
	Input _input;
	//Texture_Manager * _texture_Manager;
	SDL_Window * _window;
	SDL_Surface* _screen_surface;

	bool _is_running;
	Game();


	bool init();

	void tick(float dt);

	void game_tick(float dt);
	void exit();
};