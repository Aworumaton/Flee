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
			_player->Tick();

			_map_manager->Tick(delta_game_time);

			game_tick(delta_game_time);
		}

		{

			AnimationManager::Tick(1);
			FleeRenderer::Tick(0.0f);

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
	FleeRenderer::Initialize();
	AnimationManager::Initialize();

	_map_manager = new Map_Manager();

	//The dot that will be moving around on the screen
	_player = new Player(_map_manager, &(_input._main_agent_controls), FleeRenderer::GetCamera());

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
	//Quit SDL subsystems
	SDL_Quit();
}