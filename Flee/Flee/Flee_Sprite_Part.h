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
		None	= 0b0000000000000000,
		Ground	= 0b0000000000000001,
		Wall	= 0b0000000000000010
	};

	//Initializes position and type
	Flee_Sprite_Part(Flee_Texture* sheet,
		int x, int y,
		unsigned flags,
		SDL_Rect* rect);


	//Shows the tile
	void render(SDL_Rect& camera);

	//Get the collision box
	SDL_Rect getBox();

	bool Is_Wall();
private:
	unsigned int _flags;
	Flee_Texture * _sprite_sheet;

	SDL_Rect* _sprite_sheet_rect;

	//The attributes of the tile
	SDL_Rect _render_rect;
};

#endif