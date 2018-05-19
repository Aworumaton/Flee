#ifndef FLEE_TILE_H
#define FLEE_TILE_H

#include <SDL.h>
#include <SDL_image.h>
#include "Flee_Texture.h"
#include "Constants.h"

//The tile
class Flee_Tile
{
public:
	//Initializes position and type
	Flee_Tile(SDL_Rect bounds, int tileType, SDL_Renderer* renderer, SDL_Rect* rect);
	Flee_Tile(int x, int y, int w, int h, int tileType, SDL_Renderer* renderer, SDL_Rect* rect);
	~Flee_Tile();

	//Shows the tile
	void render(SDL_Rect& camera);

	//Get the tile type
	int getType();

	//Get the collision box
	SDL_Rect getBox();

private:
	SDL_Rect * gRect;

	Flee_Texture* gTileTexture;
	//The attributes of the tile
	SDL_Rect mBox;

	//The tile type
	int mType;
};

#endif