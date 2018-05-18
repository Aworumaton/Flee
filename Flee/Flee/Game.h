#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include <stdio.h>
#include "Controls.h"
#include "Input.h"
#include "Constants.h"
#include "Map_Creator.h"
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
	Map_Creator* _map_creator;
	SDL_Window * _window;
	SDL_Renderer* _renderer;
	SDL_Surface* _screen_surface;
	//Level camera
	SDL_Rect _camera;

	//The dot that will be moving around on the screen
	Dot* _dot;

	bool _is_running;
	Game();


	bool init();

	void tick(float dt);

	void game_tick(float dt);
	void exit();
};

#endif