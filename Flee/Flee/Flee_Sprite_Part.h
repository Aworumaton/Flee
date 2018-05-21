#ifndef Flee_Sprite_Part_H
#define Flee_Sprite_Part_H

#include <SDL.h>
#include <SDL_image.h>
#include "Flee_Texture.h"
#include "Constants.h"

//The tile
class Flee_Sprite_Part
{
public:
	enum Sprite_Flags
	{
		None			= 0b0000000000000000,
		Ground			= 0b0000000000000001,
		Wall			= 0b0000000000000010,
		Interactable	= 0b0000000000000100,
	};

	//Initializes position and type
	Flee_Sprite_Part(Flee_Texture* sheet, unsigned flags, SDL_Rect * sprite_rect);

	void Set_Position(int x, int y);

	//Shows the tile
	void render(SDL_Rect& camera, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

	//Get the collision box
	SDL_Rect getBox();
	
	SDL_Rect* Get_Render_Box();

	bool Is_Wall();
protected:
	unsigned int _flags;
	Flee_Texture * _sprite_sheet;

	SDL_Rect* _sprite_sheet_rect;

	//The attributes of the tile
	SDL_Rect _render_rect;
};

#endif