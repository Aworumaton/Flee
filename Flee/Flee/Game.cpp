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
	//Event handler
	float _spent_time = 0.0f;


	int elapsed_time = SDL_GetTicks();
	int elapsed_game_time = elapsed_time;

	int target_frame_rate = 1000 / 120;
	int target_game_frame_rate = 1000 / 60;


	while (_is_running)
	{
		int now = SDL_GetTicks();
		int delta_time = now - elapsed_time;
		int delta_game_time = now - elapsed_game_time;
		elapsed_time = now;

		//printf("Renderer frame rate: %f\n", (1000.0f / delta_time));


		//game
		if(target_game_frame_rate < delta_game_time)
		{
			elapsed_game_time = now ;
			//printf("Game frame rate: %f\n", (1000.0f / delta_game_time));

			_input.Tick(delta_game_time);
			//Move the dot
			_dot->Update();
			_dot->Update_Camera();

			_map_manager->Tick(delta_game_time);

			game_tick(delta_game_time);
		}

		//renderer
		{

			_dot->Tick_Animations(delta_time);

			//Clear screen
			SDL_SetRenderDrawColor(_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
			SDL_RenderClear(_renderer);

			_map_manager->Render(_camera);

			//Render dot
			_dot->render();

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

	Texture_Manager::Initialize(_renderer);
	
	_screen_surface = SDL_GetWindowSurface(_window);


	_camera = SDL_Rect{ 0, 0, Constants::SCREEN_WIDTH, Constants::SCREEN_HEIGHT };
	_map_manager = new Map_Manager(_renderer);

	//The dot that will be moving around on the screen
	_dot = new Dot(_renderer, _map_manager, &(_input._main_agent_controls), &_camera);

	//load level and characters


	return true;
}

void Game::tick(int dt)
{

}

void Game::game_tick(int dt)
{
	
	if (_input._game_controls.escape)
	{
		_is_running = false;
	}


	//if (_input._main_agent_controls.move_forward)
	//{
	//	printf("move_forward\n");
	//}
	//if (_input._main_agent_controls.move_left)
	//{
	//	printf("move_forward\n");
	//}
	//if (_input._main_agent_controls.move_backward)
	//{
	//	printf("move_backward\n");
	//}
	//if (_input._main_agent_controls.move_right)
	//{
	//	printf("move_right\n");
	//}
	//if (_input._main_agent_controls.action)
	//{
	//	printf("action\n");
	//}
	//printf("mouse pos: (%d,%d)\n", _input._main_agent_controls.look_at_x, _input._main_agent_controls.look_at_y);
}
void Game::exit()
{
	delete(_map_manager);
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