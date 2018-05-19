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


	SDL_Rect target_box =  SDL_Rect(mBox);

	target_box.x = mBox.x + mVelX;
	//If the dot went too far to the left or right or touched a wall
	if (target_box.x < 0)
	{
		target_box.x = 0;
	}
	else if(target_box.x + target_box.w > _map->Get_Level_Width())
	{
		target_box.x = _map->Get_Level_Width() - target_box.w;
	}
	else if(_map->touches_walls(target_box))
	{
		//move back
		target_box.x = mBox.x;
	}
	
	target_box.y = mBox.y + mVelY;

	//If the dot went too far to the left or right or touched a wall
	if (target_box.y < 0)
	{
		target_box.y = 0;
	}
	else if (target_box.y + target_box.h > _map->Get_Level_Height())
	{
		target_box.y = _map->Get_Level_Height() - target_box.h;
	}
	else if (_map->touches_walls(target_box))
	{
		//move back
		target_box.y = mBox.y;
	}

	//Move the dot up or down
	//delete(&mBox);
	mBox = target_box;
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