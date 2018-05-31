#pragma once
#include "Dot.h"

Dot::Dot(Map_Manager* map, Main_Agent_Controls* controls, FleeTransform* camera)// : _visualData("main_character_0")
{
	_camera = camera;
	_map = map;
	_controls = controls;

	_animation_timer = 0;

	//Initialize the collision box
	
	_visual = AnimationManager::GetAnimationsOf("Player");
	_visual->SetAnimation("Movement");


	//FleeRenderer::Register(&_visualData);

	_transform = &_visual->Transform;
	_actionRadius = 2 * (0.5*(_transform->Width + _transform->Height));

	_transform->X = 250;
	_transform->Y = 250;
	//mBox.w = _visual->getBox().w;
	//mBox.h = _visual->getBox().h;
}

Dot::~Dot()
{
	_transform = nullptr;
	//delete(_visual);
}

void Dot::Update()
{
	Move();


	if (_controls->on_action)
	{
		if (IsHidden)
		{
			IsHidden = false;
		}
		else
		{
			SDL_Point pos;
			Get_Position(pos.x, pos.y);

			SDL_Point target_action_pos = SDL_Point{ (_controls->look_at_y + _camera->Y),(_controls->look_at_x + _camera->X) };
			if (Constants::Get_Distance_Between(target_action_pos, pos) <= _actionRadius)
			{
				Flee_Interactable_Object* target_object = _map->Get_First_Objet_Under(target_action_pos);

				if (target_object != nullptr)
				{
					if (target_object->Is_Hiding_Place())
					{
						target_object->OnAction();
						IsHidden = true;
					}
					//else if (target_object->Is_Door() && !Constants::checkCollision(mBox, target_object->getBox()))
					//{
					//	target_object->OnAction();
					//}
				}
			}
		}
	}
}
void Dot::Move()
{
	if (IsHidden)
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

	int oldX = _transform->X;
	int oldY = _transform->Y;

	_transform->X += mVelX;

	if (_transform->X < 0)
	{
		_transform->X = 0;
	}
	else if(_transform->X + _transform->Width > _map->Get_Level_Width())
	{
		_transform->X = _map->Get_Level_Width() - _transform->Width;
	}
	else if(_map->TouchesWalls(_transform))
	{
		//move back
		_transform->X = oldX;
	}
	
	_transform->Y += mVelY;

	//If the dot went too far to the left or right or touched a wall
	if (_transform->Y < 0)
	{
		_transform->Y = 0;
	}
	else if (_transform->Y + _transform->Height > _map->Get_Level_Height())
	{
		_transform->Y = _map->Get_Level_Height() - _transform->Height;
	}
	else if (_map->TouchesWalls(_transform))
	{
		//move back
		_transform->Y = oldY;
	}

	
	//_visual->Set_Position(mBox.x, mBox.y);

	int x, y;
	Get_Position(x, y);
	_transform->Rotation = (int)(180.0f / M_PI * atan2((_controls->look_at_y + _camera->Y) - y,
							(_controls->look_at_x + _camera->X) - x));

	//normalize
	_transform->Rotation = (450 + (int)_transform->Rotation) % 360;


	printf("dot pos (%d, %d)\n", x, y);


}

void Dot::Update_Camera()
{
	if (IsHidden)
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