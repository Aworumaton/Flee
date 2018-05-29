#pragma once
#include "Dot.h"

Dot::Dot(Map_Manager* map, Main_Agent_Controls* controls, Transform* camera)
{
	_camera = camera;
	_map = map;
	_controls = controls;

	_animation_timer = 0;

	//Initialize the collision box
	
	//_visual = Texture_Manager::Create_Animated_Sprite("main_character");

	_is_Hidden = false;

	mBox.x = 250;
	mBox.y = 250;
	//mBox.w = _visual->getBox().w;
	//mBox.h = _visual->getBox().h;
}

Dot::~Dot()
{
	//delete(_visual);
}

void Dot::Update()
{
	move();
	if (_controls->on_action)
	{
		if (_is_Hidden)
		{
			_is_Hidden = false;
		}
		else
		{
			SDL_Point pos;
			Get_Position(pos.x, pos.y);

			SDL_Point target_action_pos = SDL_Point{ (_controls->look_at_y + _camera->Y),(_controls->look_at_x + _camera->X) };
			if (Constants::Get_Distance_Between(target_action_pos, pos) <= ACTION_RADIUS)
			{
				Flee_Interactable_Object* target_object = _map->Get_First_Objet_Under(target_action_pos);

				if (target_object != nullptr)
				{
					if (target_object->Is_Hiding_Place())
					{
						target_object->OnAction();
						_is_Hidden = true;
					}
					else if (target_object->Is_Door() && !Constants::checkCollision(mBox, target_object->getBox()))
					{
						target_object->OnAction();
					}
				}
			}
		}
	}
}
void Dot::move()
{
	if (_is_Hidden)
	{
		return;
	}

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
	
	//_visual->Set_Position(mBox.x, mBox.y);

	int x, y;
	Get_Position(x, y);
	_rotation = (int)(180.0f / M_PI * atan2((_controls->look_at_y + _camera->Y) - y,
							(_controls->look_at_x + _camera->X) - x));

	//normalize
	_rotation = (450 + (int)_rotation) % 360;


	printf("dot pos (%d, %d)\n", x, y);


}

void Dot::Update_Camera()
{
	if (_is_Hidden)
	{
		return;
	}

	int x, y;
	Get_Position(x, y);
	//Center the camera over the dot
	_camera->X = x - _camera->Width / 2;
	_camera->Y = y - _camera->Height / 2;

	//Clamp the camera in bounds
	if (_camera->X < 0)
	{
		_camera->X = 0;
	}
	if (_camera->Y < 0)
	{
		_camera->Y = 0;
	}
	if (_camera->X > _map->Get_Level_Width() - _camera->Width)
	{
		_camera->X = _map->Get_Level_Width() - _camera->Width;
	}
	if (_camera->Y > _map->Get_Level_Height() - _camera->Height)
	{
		_camera->Y = _map->Get_Level_Height() - _camera->Height;
	}
	printf("dot pos (%d, %d)       camera dot pos (%d, %d)\n", x, y, _camera->X, _camera->Y);
}

void Dot::Tick_Animations(int dt)
{
	_animation_timer += dt;
	if (_animation_frame_rate < _animation_timer)
	{
		_animation_timer = _animation_timer % _animation_frame_rate;
		//_visual->Set_Frame_Index((_visual->Get_Frame_Index()+1)% _visual->Get_Frame_Count());


		//_visual->Tick_Animations(dt);
	}
}

void Dot::render()
{
	if (!_is_Hidden)
	{
		//_visual->Render(*_camera, _rotation);
	}
}