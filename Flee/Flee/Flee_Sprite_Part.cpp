#pragma once
#include "Flee_Sprite_Part.h"


Flee_Sprite_Part::Flee_Sprite_Part(Flee_Texture* sheet, SDL_Rect bounds, int tileType, SDL_Rect* rect)
{
	gRect = rect;

	mBox = bounds;

	//Get the tile type
	mType = tileType;


	_sprite_sheet = sheet;
}

//Flee_Tile::~Flee_Tile()
//{
//	gTileTexture->free();
//}

void Flee_Sprite_Part::render(SDL_Rect& camera)
{
	//If the tile is on screen
	if (Constants::checkCollision(camera, mBox))
	{
		//Show the tile
		_sprite_sheet->render(mBox.x - camera.x, mBox.y - camera.y, gRect);
	}
}

int Flee_Sprite_Part::getType()
{
	return mType;
}

SDL_Rect Flee_Sprite_Part::getBox()
{
	return mBox;
}