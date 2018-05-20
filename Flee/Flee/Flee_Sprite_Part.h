#ifndef FLEE_TILE_H
#define FLEE_TILE_H

#include <SDL.h>
#include <SDL_image.h>
#include "Flee_Texture.h"
#include "Constants.h"

//The tile
class Flee_Sprite_Part
{
public:
	enum Tile_Type
	{
		Invalid = -1,
		TILE_RED = 0,
		TILE_GREEN = 1,
		TILE_BLUE = 2,
		TILE_CENTER = 3,
		TILE_TOP = 4,
		TILE_TOPRIGHT = 5,
		TILE_RIGHT = 6,
		TILE_BOTTOMRIGHT = 7,
		TILE_BOTTOM = 8,
		TILE_BOTTOMLEFT = 9,
		TILE_LEFT = 10,
		TILE_TOPLEFT = 11,
		DOOR_VERTICAL,
		DOOR_HORIZONTAL,
		Count = 12
	};

	//Initializes position and type
	Flee_Sprite_Part(Flee_Texture* sheet, SDL_Rect bounds, int tileType, SDL_Rect* rect);


	//Shows the tile
	void render(SDL_Rect& camera);

	//Get the tile type
	int getType();

	//Get the collision box
	SDL_Rect getBox();

private:
	Flee_Texture * _sprite_sheet;

	SDL_Rect * gRect;

	//The attributes of the tile
	SDL_Rect mBox;

	//The tile type
	int mType;
};

#endif