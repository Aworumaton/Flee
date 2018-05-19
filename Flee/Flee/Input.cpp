#pragma once
#include "Input.h"

Input::Input()
{
	force_exit = false;

	//_game_controls = new Game_Controls();
	//_main_agent_controls = new Main_Agent_Controls();
}

Input::~Input()
{
}

void Input::Tick(float dt)
{
	bool quit = false;
	SDL_Event e;

	while (SDL_PollEvent(&e) != 0)
	{
		switch (e.type)
		{
		case SDL_QUIT:
			force_exit = true;
			break;

		case SDL_KEYDOWN:
			switch (e.key.keysym.sym)
			{
			case SDLK_p:
			case SDLK_PAUSE:
				_game_controls.escape = true;
				break;
			case SDLK_w:
			case SDLK_UP:
				_main_agent_controls.move_forward = true;
				break;
			case SDLK_a:
			case SDLK_LEFT:
				_main_agent_controls.move_left = true;
				break;
			case SDLK_s:
			case SDLK_DOWN:
				_main_agent_controls.move_backward = true;
				break;
			case SDLK_d:
			case SDLK_RIGHT:
				_main_agent_controls.move_right = true;
				break;
			case SDLK_LSHIFT:
			case SDLK_RSHIFT:
				_main_agent_controls.sprint = true;
				break;
			case SDLK_e:
			case SDLK_f:
				_main_agent_controls.action = true;
				break;
			default:
				break;
			}
			break;

		case SDL_KEYUP:
			switch (e.key.keysym.sym)
			{
			case SDLK_p:
			case SDLK_PAUSE:
				_game_controls.escape = false;
				break;
			case SDLK_w:
			case SDLK_UP:
				_main_agent_controls.move_forward = false;
				break;
			case SDLK_a:
			case SDLK_LEFT:
				_main_agent_controls.move_left = false;
				break;
			case SDLK_s:
			case SDLK_DOWN:
				_main_agent_controls.move_backward = false;
				break;
			case SDLK_d:
			case SDLK_RIGHT:
				_main_agent_controls.move_right = false;
				break;
			case SDLK_LSHIFT:
			case SDLK_RSHIFT:
				_main_agent_controls.sprint = false;
				break;
			case SDLK_e:
			case SDLK_f:
				_main_agent_controls.action = false;
				break;
			default:
				break;
			}
			break;
		default:
			break;
		}
	}
}
