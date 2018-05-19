#pragma once
#include "Flee_Interactable.h"

Flee_Interactable::Flee_Interactable(SDL_Rect bounds, int tileType, SDL_Renderer* renderer, SDL_Rect* rect) : Flee_Texture(renderer)
{
	gRect = rect;

	mBox = bounds;

	//Get the tile type
	mType = tileType;

	//Load tile texture
	if (!loadFromFile("Resources/interactables.png"))
	{
		printf("Failed to load tile set texture!\n");
	}
}
Flee_Interactable::Flee_Interactable(int x, int y, int w, int h, int tileType, SDL_Renderer* renderer, SDL_Rect* rect)
	: Flee_Interactable(SDL_Rect{ x, y, w, h }, tileType, renderer, rect) {}

//Flee_Tile::~Flee_Tile()
//{
//	gTileTexture->free();
//}

void Flee_Interactable::render(SDL_Rect& camera)
{
	//If the tile is on screen
	if (Constants::checkCollision(camera, mBox))
	{
		//Show the tile
		Flee_Texture::render(mBox.x - camera.x, mBox.y - camera.y, gRect);
	}
}

int Flee_Interactable::getType()
{
	return mType;
}

SDL_Rect Flee_Interactable::getBox()
{
	return mBox;
}