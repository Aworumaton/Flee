#pragma once
#include "Game.h"

Game* Game::CreateGame()
{
	Game* g = new Game();
	if (!g->Initialize())
	{
		printf("Failed to initialize!\n");
	}
	return g;
}

void Game::Run()
{
	_isRunning = true;
	//Event handler
	float _spent_time = 0.0f;


	int elapsed_time = SDL_GetTicks();
	int elapsed_game_time = elapsed_time;

	int target_frame_rate = 1000 / 120;
	int target_game_frame_rate = 1000 / 60;


	while (_isRunning)
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

			_scene->Tick(delta_game_time);

			GameTick(delta_game_time);
		}

		{

			AnimationManager::Tick(1);
			FleeRenderer::Tick(0.0f);

		}
	}
}

Game::~Game()
{
	Exit();
}

Game::Game()
{
}


bool Game::Initialize()
{
	FleeRenderer::Initialize();
	AnimationManager::Initialize();

	_scene = new Scene();

	//The dot that will be moving around on the screen
	_player = new Player(_scene, &(_input._main_agent_controls), FleeRenderer::GetCamera());

	//load level and characters


	return true;
}

void Game::Tick(int dt)
{

}

void Game::GameTick(int dt)
{
	
	if (_input._game_controls.escape)
	{
		_isRunning = false;
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
void Game::Exit()
{
	//Quit SDL subsystems
	SDL_Quit();
}