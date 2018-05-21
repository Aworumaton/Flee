#ifndef Flee_Sprite_H
#define Flee_Sprite_H

#include "Flee_Sprite_Part.h"

class Flee_Animated_Sprite_Part
{
	Flee_Animated_Sprite_Part(Flee_Sprite_Part* sprites, int sprite_count, int animation_frame_rate = -1, int current_frame_index = 0)
	{
		_frame_index = current_frame_index;
		
		_sprites = sprites;
		_sprite_count = sprite_count;
		
		_animation_frame_rate = animation_frame_rate;
	};

	void Render(SDL_Rect& camera)
	{
		if (_frame_index >= 0 && _frame_index < _sprite_count)
		{
			_sprites[_frame_index].render(camera);
		}
	};

	void Tick_Animations(int dt)
	{
		if (_animation_frame_rate >= 0)
		{
			_animation_timer += dt;
			if (_animation_frame_rate < _animation_timer)
			{
				_animation_timer = _animation_timer % _animation_frame_rate;
				_frame_index = (_frame_index+1) % _sprite_count;
			}
		}
	};

	int Get_Frame_Index()
	{
		return _frame_index;
	};

	int Set_Frame_Index(int index)
	{
		_frame_index = index;
	};

private :
	Flee_Sprite_Part * _sprites;
	int _sprite_count;
	
	int _frame_index;

	int _animation_timer;
	int _animation_frame_rate;
};
#endif
