#ifndef Flee_Sprite_Part_H
#define Flee_Sprite_Part_H

#include <SDL.h>
#include <SDL_image.h>
#include "Flee_Sprite_Part_Base.h"
#include "Flee_Texture.h"
#include "Constants.h"

//The tile
class Flee_Sprite_Part : Flee_Sprite_Part_Base
{
public:

	//Initializes position and type
	Flee_Sprite_Part(Flee_Texture* sheet, unsigned flags, SDL_Rect * sprite_rect);

	void Set_Position(int x, int y);

	//Shows the tile
	void Render(SDL_Rect& camera, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

	//Get the collision box
	SDL_Rect getBox();

	bool Is_Wall();

	unsigned int Get_Flags();
private:
	unsigned int _flags;
	Flee_Texture * _sprite_sheet;

	SDL_Rect* _sprite_sheet_rect;

	//The attributes of the tile
	SDL_Rect _render_rect;
};
#endif