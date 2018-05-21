#ifndef Flee_Sprite_H
#define Flee_Sprite_H

#include <SDL.h>
#include "Flee_Sprite_Part_Base.h"
#include "Flee_Texture.h"

class Flee_Animated_Sprite_Part : Flee_Sprite_Part_Base
{
public:
	Flee_Animated_Sprite_Part(Flee_Texture* sheet, int sprite_count, SDL_Rect** sprite_positions, int animation_frame_rate = -1, int current_frame_index = 0);

	void Render(SDL_Rect& camera, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);
	void Set_Position(int x, int y);
	//Get the collision box
	SDL_Rect getBox();


	void Tick_Animations(int dt);
	

	int Get_Frame_Index();
	int Get_Frame_Count();

	void Set_Frame_Index(int index);


private :
	unsigned int _flags;
	Flee_Texture * _sprite_sheet;
	SDL_Point _render_position;

	SDL_Rect** _sprite_positions;
	int _sprite_count;
	
	int _frame_index;

	int _animation_timer;
	int _animation_frame_rate;
};



#endif