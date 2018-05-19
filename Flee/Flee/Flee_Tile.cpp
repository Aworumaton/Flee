#pragma once
#include "Flee_Tile.h"


Flee_Tile::Flee_Tile(SDL_Rect bounds, int tileType, SDL_Renderer* renderer, SDL_Rect* rect)
{
	gTileTexture = new Flee_Texture(renderer);
	gRect = rect;

	mBox = bounds;

	//Get the tile type
	mType = tileType;

	//Load tile texture
	if (!gTileTexture->loadFromFile("Resources/tiles.png"))
	{
		printf("Failed to load tile set texture!\n");
	}
}
Flee_Tile::Flee_Tile(int x, int y, int w, int h, int tileType, SDL_Renderer* renderer, SDL_Rect* rect)
	: Flee_Tile(SDL_Rect{ x, y, w, h}, tileType, renderer, rect){}

Flee_Tile::~Flee_Tile()
{
	gTileTexture->free();
}

void Flee_Tile::render(SDL_Rect& camera)
{
	//If the tile is on screen
	if (Constants::checkCollision(camera, mBox))
	{
		//Show the tile
		gTileTexture->render(mBox.x - camera.x, mBox.y - camera.y, gRect);
	}
}

int Flee_Tile::getType()
{
	return mType;
}

SDL_Rect Flee_Tile::getBox()
{
	return mBox;
}