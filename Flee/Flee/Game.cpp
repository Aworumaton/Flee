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

	Uint32 elapsed_time = SDL_GetTicks();
	Uint32 target_frame_rate = (Uint32)1000 / (Uint32)60;

	while (_isRunning)
	{
		Uint32 now = SDL_GetTicks();
		Uint32 delta_time = now - elapsed_time;
		if (delta_time > 0)
		{
			if(target_frame_rate < delta_time)
			{
				elapsed_time = now ;

				_input.Tick(delta_time);

				_player->Tick(delta_time);


				_enemy->SetTarget(_player->Transform);
				//FleeTransform* testTarget = new FleeTransform();
				//testTarget->X = _input._main_agent_controls.look_at_x + FleeRenderer::GetCamera()->X;
				//testTarget->Y = _input._main_agent_controls.look_at_y + FleeRenderer::GetCamera()->Y;
				//_enemy->SetTarget(testTarget);

				_enemy->Tick(delta_time);

				_scene->Tick(delta_time);

				GameTick(delta_time);


				AnimationManager::Tick(delta_time);
				FleeRenderer::Tick(delta_time);
			}
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

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		return false;
	}

	FleeRenderer::Initialize();
	AnimationManager::Initialize();

	_scene = new Scene();
	_scene->Initialize();

	_navMap = new NavigationGridMap();
	_navMap->Initialize(_scene);
	//The dot that will be moving around on the screen
	_player = new Player(_scene, &(_input._main_agent_controls), FleeRenderer::GetCamera());
	_enemy = new Enemy(_scene, _navMap);

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
}
void Game::Exit()
{
	//Quit SDL subsystems
	SDL_Quit();
}