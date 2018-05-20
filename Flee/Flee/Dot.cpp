#pragma once
#include "Dot.h"

Dot::Dot(SDL_Renderer* renderer, Map_Manager* map, Main_Agent_Controls* controls, SDL_Rect* camera)
{
	_camera = camera;
	_map = map;
	_controls = controls;

	_animation_timer = 0;

	//Initialize the collision box
	mBox.x = 0;
	mBox.y = 0;
	mBox.w = DOT_WIDTH;
	mBox.h = DOT_HEIGHT;

	animation_Frame = SDL_Rect{ 0,0,DOT_WIDTH,DOT_HEIGHT };

	gDotTexture = new Flee_Texture(renderer);

	//Load dot texture
	if (!gDotTexture->loadFromFile("Resources/main_character.bmp"))
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
	mBox = target_box;

	_rotation = (int)(180.0f / M_PI * atan2((_controls->look_at_y + _camera->y) - (mBox.y + (DOT_HEIGHT*0.5f)),
							(_controls->look_at_x + _camera->x) - (mBox.x + (DOT_WIDTH*0.5f))));

	//normalize
	_rotation = (450 + (int)_rotation) % 360;

}

void Dot::Update_Camera()
{
	//Center the camera over the dot
	_camera->x = (mBox.x + DOT_WIDTH / 2) - Constants::SCREEN_WIDTH / 2;
	_camera->y = (mBox.y + DOT_HEIGHT / 2) - Constants::SCREEN_HEIGHT / 2;

	//Clamp the camera in bounds
	if (_camera->x < 0)
	{
		_camera->x = 0;
	}
	if (_camera->y < 0)
	{
		_camera->y = 0;
	}
	if (_camera->x > _map->Get_Level_Width() - _camera->w)
	{
		_camera->x = _map->Get_Level_Width() - _camera->w;
	}
	if (_camera->y > _map->Get_Level_Height() - _camera->h)
	{
		_camera->y = _map->Get_Level_Height() - _camera->h;
	}
}

void Dot::Tick_Animations(int dt)
{
	_animation_timer += dt;
	if (_animation_frame_rate < _animation_timer)
	{
		_animation_timer = _animation_timer % _animation_frame_rate;
		animation_Frame.x = (animation_Frame.x + DOT_WIDTH) % (DOT_WIDTH * 4);
	}
}

void Dot::render()
{

	//Show the dot
	gDotTexture->render(mBox.x - _camera->x, mBox.y - _camera->y, &animation_Frame, _rotation);
}