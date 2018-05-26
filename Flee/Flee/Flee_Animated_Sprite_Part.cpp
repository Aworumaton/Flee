#include "Flee_Animated_Sprite_Part.h"

Flee_Animated_Sprite_Part::Flee_Animated_Sprite_Part(Flee_Texture* sheet, int sprite_count, SDL_Rect** sprite_positions, unsigned int* flags, int animation_frame_rate, int current_frame_index)
{
	_sprite_sheet = sheet;
	_frame_index = current_frame_index;
	_flags = flags;

	_sprite_positions = sprite_positions;
	_sprite_count = sprite_count;

	_animation_frame_rate = animation_frame_rate;
	_render_position = SDL_Point{0,0};
}

void Flee_Animated_Sprite_Part::Render(SDL_Rect& camera, double angle, SDL_Point* center, SDL_RendererFlip flip)
{
	if (_frame_index >= 0 && _frame_index < _sprite_count)
	{
		_sprite_sheet->render(_render_position.x - camera.x, _render_position.y - camera.y, _sprite_positions[_frame_index], angle, center, flip);
	}
}

void Flee_Animated_Sprite_Part::Set_Position(int x, int y)
{
	_render_position.x = x;
	_render_position.y = y;
}

void Flee_Animated_Sprite_Part::Tick_Animations(int dt)
{
	if (_animation_frame_rate >= 0)
	{
		_animation_timer += dt;
		if (_animation_frame_rate < _animation_timer)
		{
			_animation_timer = _animation_timer % _animation_frame_rate;
			_frame_index = (_frame_index + 1) % _sprite_count;
		}
	}
}

int Flee_Animated_Sprite_Part::Get_Frame_Index()
{
	return _frame_index;
}

int Flee_Animated_Sprite_Part::Get_Frame_Count()
{
	return _sprite_count;
}

void Flee_Animated_Sprite_Part::Set_Frame_Index(int index)
{
	_frame_index = index;
}

SDL_Rect Flee_Animated_Sprite_Part::getBox()
{
	return SDL_Rect{ _render_position.x, _render_position.y, _sprite_positions[_frame_index]->w, _sprite_positions[_frame_index]->h};
}

unsigned int Flee_Animated_Sprite_Part::Get_Flags()
{
	return _flags[_frame_index];
}