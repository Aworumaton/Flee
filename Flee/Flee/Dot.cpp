#pragma once
#include "Dot.h"

Dot::Dot(SDL_Renderer* renderer, Main_Agent_Controls* controls) : Dot()
{
	gDotTexture = new Flee_Texture(renderer);
	_controls = controls;

	//Load dot texture
	if (!gDotTexture->loadFromFile("Resources/dot.bmp"))
	{
		printf("Failed to load dot texture!\n");
	}
}

Dot::Dot()
{
	//Initialize the collision box
	mBox.x = 0;
	mBox.y = 0;
	mBox.w = DOT_WIDTH;
	mBox.h = DOT_HEIGHT;
}

Dot::~Dot()
{
	gDotTexture->free();
}

void Dot::move(Flee_Tile *tiles[])
{
	int vel = DEFAULT_DOT_VEL;
	if (_controls->sprint)
	{
		vel = MAX_DOT_VEL;
	}

	int mVelY = 0;
	int mVelX = 0;

	if (_controls->move_forward)
	{
		mVelY -= vel;
	}
	if (_controls->move_backward)
	{
		mVelY += vel;
	}
	if (_controls->move_left)
	{
		mVelX -= vel;
	}
	if (_controls->move_right)
	{
		mVelX += vel;
	}




	//Move the dot left or right
	mBox.x += mVelX;
	
	//If the dot went too far to the left or right or touched a wall
	if ((mBox.x < 0) || (mBox.x + DOT_WIDTH > Constants::LEVEL_WIDTH) || touchesWall(mBox, tiles))
	{
		//move back
		mBox.x -= mVelX;
	}
	
	//Move the dot up or down
	mBox.y += mVelY;
	
	//If the dot went too far up or down or touched a wall
	if ((mBox.y < 0) || (mBox.y + DOT_HEIGHT > Constants::LEVEL_HEIGHT) || touchesWall(mBox, tiles))
	{
		//move back
		mBox.y -= mVelY;
	}
}

bool Dot::touchesWall(SDL_Rect box, Flee_Tile* tiles[])
{
	//Go through the tiles
	for (int i = 0; i < Constants::TOTAL_TILES; ++i)
	{
		//If the tile is a wall type tile
		if ((tiles[i]->getType() >= Constants::Tile_Type::TILE_CENTER) && (tiles[i]->getType() <= Constants::Tile_Type::TILE_TOPLEFT))
		{
			//If the collision box touches the wall tile
			if (Constants::checkCollision(box, tiles[i]->getBox()))
			{
				return true;
			}
		}
	}

	//If no wall tiles were touched
	return false;
}

void Dot::setCamera(SDL_Rect& camera)
{
	//Center the camera over the dot
	camera.x = (mBox.x + DOT_WIDTH / 2) - Constants::SCREEN_WIDTH / 2;
	camera.y = (mBox.y + DOT_HEIGHT / 2) - Constants::SCREEN_HEIGHT / 2;

	//Keep the camera in bounds
	if (camera.x < 0)
	{
		camera.x = 0;
	}
	if (camera.y < 0)
	{
		camera.y = 0;
	}
	if (camera.x > Constants::LEVEL_WIDTH - camera.w)
	{
		camera.x = Constants::LEVEL_WIDTH - camera.w;
	}
	if (camera.y > Constants::LEVEL_HEIGHT - camera.h)
	{
		camera.y = Constants::LEVEL_HEIGHT - camera.h;
	}
}

void Dot::render(SDL_Rect& camera)
{
	//Show the dot
	gDotTexture->render(mBox.x - camera.x, mBox.y - camera.y);
}