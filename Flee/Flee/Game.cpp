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


	_screen_surface = SDL_GetWindowSurface(_window);
	//_texture_Manager = new Texture_Manager(_window);
	_map_creator = new Map_Creator(_window);

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
	if (_window != NULL)
	{
		//Destroy window
		SDL_DestroyWindow(_window);
		_window = NULL;
	}

	//Quit SDL subsystems
	SDL_Quit();
}