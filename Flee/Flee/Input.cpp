#pragma once
#include "Input.h"

Input::Input()
{
	force_exit = false;

	_game_controls.reset();
	_main_agent_controls.reset();
}

Input::~Input()
{
}

void Input::Tick(int dt)
{
	_main_agent_controls.on_action = false;
	bool quit = false;
	SDL_Event e;
	//if (e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP) { //Get mouse position int x, y; SDL_GetMouseState( &x, &y );
	while (SDL_PollEvent(&e) != 0)
	{
		switch (e.type)
		{
		case SDL_QUIT:
			force_exit = true;
			break;

		case SDL_MOUSEMOTION:
			SDL_GetMouseState(&_main_agent_controls.look_at_x, &_main_agent_controls.look_at_y);
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
				_main_agent_controls.on_action = !(_main_agent_controls.active_action);

				_main_agent_controls.active_action = true;

				printf("try: _main_agent_controls.active_action\n");
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
				_main_agent_controls.on_action = false;
				_main_agent_controls.active_action = false;
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
