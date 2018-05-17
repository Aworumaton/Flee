
#include <SDL.h>
#include <stdio.h>
#include "Controls.h"
#include "Texture_Manager.cpp"
#include "Input.cpp"

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

	void run()
	{
		_is_running = true;
		float dt = 0.0f;
		//Event handler
		while (_is_running)
		{
			_input.Tick(dt);
			game_tick(dt);


			//Apply the image
			//SDL_BlitSurface(gHelloWorld, NULL, gScreenSurface, NULL);

			//Update the surface
			SDL_UpdateWindowSurface(_window);
		}
	}

	~Game()
	{
		exit();
	}
private:
	Input _input;
	//Texture_Manager * _texture_Manager;
	SDL_Window * _window;
	SDL_Surface* _screen_surface;

	bool _is_running;
	Game()
	{

	}


	bool init()
	{
		//Initialization flag
		bool success = true;

		//Initialize SDL
		if (SDL_Init(SDL_INIT_VIDEO) < 0)
		{
			printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
			return false;
		}
		else
		{
			//Create window
			_window = SDL_CreateWindow("Flee", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
			if (_window == NULL)
			{
				printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
				return false;
			}
		}


		_screen_surface = SDL_GetWindowSurface(_window);
		//_texture_Manager = new Texture_Manager(_window);

		//load level and characters


		return true;
	}

	void tick(float dt)
	{

	}

	void game_tick(float dt)
	{

		if (_main_agent_controls.move_forward)
		{
			printf("move_forward\n");
		}
		if (_main_agent_controls.move_left)
		{
			printf("move_forward\n");
		}
		if (_main_agent_controls.move_backward)
		{
			printf("move_backward\n");
		}
		if (_main_agent_controls.move_right)
		{
			printf("move_right\n");
		}
		if (_main_agent_controls.action)
		{
			printf("action\n");
		}
	}
	void exit()
	{
		if (_window != NULL)
		{
			//Destroy window
			SDL_DestroyWindow(_window);
			_window = NULL;
		}

		//Quit SDL subsystems
		SDL_Quit();
	}
};