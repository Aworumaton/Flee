#ifndef FLEE_INTERACTABLE_H
#define FLEE_INTERACTABLE_H

#include <SDL.h>
#include <SDL_image.h>
#include "Flee_Texture.h"
#include "Constants.h"

//The Interactable
class Flee_Interactable : Flee_Texture
{
public:
	enum Interactable_Type
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
	Flee_Interactable(SDL_Rect bounds, int tileType, SDL_Renderer* renderer, SDL_Rect* rect);
	Flee_Interactable(int x, int y, int w, int h, int tileType, SDL_Renderer* renderer, SDL_Rect* rect);


	//Shows the tile
	void render(SDL_Rect& camera);

	//Get the tile type
	int getType();

	//Get the collision box
	SDL_Rect getBox();

private:
	SDL_Rect * gRect;

	//The attributes of the tile
	SDL_Rect mBox;

	//The tile type
	int mType;
};

#endif