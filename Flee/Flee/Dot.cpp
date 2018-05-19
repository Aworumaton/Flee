#pragma once
#include "Dot.h"

Dot::Dot(SDL_Renderer* renderer, Map_Manager* map, Main_Agent_Controls* controls)
{

	_map = map;
	_controls = controls;

	//Initialize the collision box
	mBox.x = 0;
	mBox.y = 0;
	mBox.w = DOT_WIDTH;
	mBox.h = DOT_HEIGHT;


	gDotTexture = new Flee_Texture(renderer);

	//Load dot texture
	if (!gDotTexture->loadFromFile("Resources/dot.bmp"))
	{
		printf("Failed to load dot texture!\n");
	}
}
Dot::~Dot()
{
	gDotTexture->free();
}

void Dot::move()
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
	if ((mBox.x < 0) || (mBox.x + mBox.w > _map->Get_Level_Width()) || _map->touches_walls(mBox))
	{
		//move back
		mBox.x -= mVelX;
	}

	//Move the dot up or down
	mBox.y += mVelY;

	//If the dot went too far up or down or touched a wall
	if ((mBox.y < 0) || (mBox.y + mBox.h > _map->Get_Level_Height()) || _map->touches_walls(mBox))
	{
		//move back
		mBox.y -= mVelY;
	}
}

void Dot::setCamera(SDL_Rect& camera)
{
	//Center the camera over the dot
	camera.x = (mBox.x + DOT_WIDTH / 2) - Constants::SCREEN_WIDTH / 2;
	camera.y = (mBox.y + DOT_HEIGHT / 2) - Constants::SCREEN_HEIGHT / 2;

	//Clamp the camera in bounds
	if (camera.x < 0)
	{
		camera.x = 0;
	}
	if (camera.y < 0)
	{
		camera.y = 0;
	}
	if (camera.x > _map->Get_Level_Width() - camera.w)
	{
		camera.x = _map->Get_Level_Width() - camera.w;
	}
	if (camera.y > _map->Get_Level_Height() - camera.h)
	{
		camera.y = _map->Get_Level_Height() - camera.h;
	}
}

void Dot::render(SDL_Rect& camera)
{
	//Show the dot
	gDotTexture->render(mBox.x - camera.x, mBox.y - camera.y);
}