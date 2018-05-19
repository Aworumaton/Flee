#pragma once
#include "Game.h"

Game* Game::create_game()
{
	Game* g = new Game();
	if (!g->init())
	{
		printf("Failed to initialize!\n");
	}
	return g;
}

void Game::run()
{
	_is_running = true;
	float dt = 0.0f;
	//Event handler
	float _spent_time = 0.0f;

	while (_is_running)
	{
		//game
		{
			_input.Tick(dt);


			//Move the dot
			_dot->move(_map_creator->_tileSet);
			_dot->setCamera(_camera);


			game_tick(dt);
		}

		//renderer
		{
			//Clear screen
			SDL_SetRenderDrawColor(_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
			SDL_RenderClear(_renderer);

			_map_creator->Render(_camera);

			//Render dot
			_dot->render(_camera);

			//Update screen
			SDL_RenderPresent(_renderer);
		}
	}
}

Game::~Game()
{
	exit();
}

Game::Game()
{
}


bool Game::init()
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
		_window = SDL_CreateWindow("Flee", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, Constants::SCREEN_WIDTH, Constants::SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (_window == NULL)
		{
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			return false;
		}
	}

	//Create renderer for window
	_renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	//Initialize renderer color
	SDL_SetRenderDrawColor(_renderer, 0xFF, 0xFF, 0xFF, 0xFF);


	_screen_surface = SDL_GetWindowSurface(_window);
	//_texture_Manager = new Texture_Manager(_window);


	_camera = SDL_Rect{ 0, 0, Constants::SCREEN_WIDTH, Constants::SCREEN_HEIGHT };
	_map_creator = new Map_Creator(_renderer);

	//The dot that will be moving around on the screen
	_dot = new Dot(_renderer, &(_input._main_agent_controls));

	//load level and characters


	return true;
}

void Game::tick(float dt)
{

}

void Game::game_tick(float dt)
{

	if (_input._main_agent_controls.move_forward)
	{
		printf("move_forward\n");
	}
	if (_input._main_agent_controls.move_left)
	{
		printf("move_forward\n");
	}
	if (_input._main_agent_controls.move_backward)
	{
		printf("move_backward\n");
	}
	if (_input._main_agent_controls.move_right)
	{
		printf("move_right\n");
	}
	if (_input._main_agent_controls.action)
	{
		printf("action\n");
	}
}
void Game::exit()
{
	if (_renderer != NULL)
	{
		//Destroy renderer
		SDL_DestroyRenderer(_renderer);
		_renderer = NULL;
	}
	if (_window != NULL)
	{
		//Destroy window
		SDL_DestroyWindow(_window);
		_window = NULL;
	}

	//Quit SDL subsystems
	SDL_Quit();
}