#pragma once
#include <SDL.h>
#include <stdio.h>
#include "Controls.h"
#include "Texture_Manager.h"
#include "Input.h"

class Game
{
public:
	static Game create_game()
	{
		Game g;
		if (!g.init())
		{
			printf("Failed to initialize!\n");
		}
		return g;
	}

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