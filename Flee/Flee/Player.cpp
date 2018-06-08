#pragma once
#include "Player.h"

Player::Player(Scene* map, Main_Agent_Controls* controls, FleeTransform* camera)// : _visualData("main_character_0")
{
	_map = map;
	_camera = camera;
	_controls = controls;

	
	_visualData = AnimationManager::CreateAnimationsOf("Player", Constants::VisualLayers::DynamicObjectsLayer);
	_visualData->SetAnimation("Idle");
	_isMoving = false;
	_isRunning = false;

	Transform = _visualData->Transform;
	_actionRadius = 2 * (0.5*(Transform->Width + Transform->Height));

	Transform->X = 250;
	Transform->Y = 250;
	//mBox.w = _visual->getBox().w;
	//mBox.h = _visual->getBox().h;
}

Player::~Player()
{
	Character::~Character();
}

void Player::Tick(int dt)
{
	Move(dt);


	if (_controls->on_action)
	{
		if (_isHidden)
		{
			SetIsHidden(false);
		}
		else
		{
			SDL_Point pos;
			GetPosition(pos.x, pos.y);

			SDL_Point target_action_pos = SDL_Point{ (_controls->look_at_y + _camera->Y),(_controls->look_at_x + _camera->X) };
			if (Constants::Get_Distance_Between(target_action_pos, pos) <= _actionRadius)
			{
				GameObject* target_object = _map->GetFirstObjetUnder(target_action_pos);

				if (target_object != nullptr)
				{
					if (target_object->HasFlag(GameEntityFlags::Hiding_Place))
					{
						//target_object->OnAction();
						SetIsHidden(true);
					}
					else if (target_object->HasFlag(GameEntityFlags::Door) && !Constants::CheckCollision(Transform, target_object->Transform))
					{
						((Door*)target_object)->Toggle();
					}
				}
			}
		}
	}


	UpdateCamera();
}
void Player::Move(int dt)
{
	if (_isHidden)
	{
		return;
	}

	int vel = 0;
	if (_controls->sprint)
	{
		vel = DEFAULT_VELOCITY * dt * SPRINT_MULTIPTLIER;
	}
	else
	{
		vel = DEFAULT_VELOCITY * dt;
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

	int oldX = Transform->X;
	int oldY = Transform->Y;

	Transform->X += mVelX;

	if (Transform->X < 0)
	{
		Transform->X = 0;
	}
	else if(Transform->X + Transform->Width > _map->GetLevelWidth())
	{
		Transform->X = _map->GetLevelWidth() - Transform->Width;
	}
	else if(_map->IsBlocked(Transform))
	{
		//move back
		Transform->X = oldX;
	}
	
	Transform->Y += mVelY;

	//If went too far to the left or right or touched a wall
	if (Transform->Y < 0)
	{
		Transform->Y = 0;
	}
	else if (Transform->Y + Transform->Height > _map->GetLevelHeight())
	{
		Transform->Y = _map->GetLevelHeight() - Transform->Height;
	}
	else if (_map->IsBlocked(Transform))
	{
		//move back
		Transform->Y = oldY;
	}

	int x, y;
	GetPosition(x, y);
	Transform->Rotation = (int)(180.0f / M_PI * atan2((_controls->look_at_y + _camera->Y) - y,
							(_controls->look_at_x + _camera->X) - x));

	//normalize
	Transform->Rotation = (450 + (int)Transform->Rotation) % 360;


	bool willMove = oldX != Transform->X || oldY != Transform->Y;
	if (willMove && (!_isMoving || _isRunning != _controls->sprint))
	{
		_isMoving = true;
		if (!_controls->sprint)
		{
			_isRunning = false;
			_visualData->SetAnimation("Walk");
		}
		else if (!_isRunning && _controls->sprint)
		{
			_isRunning = true;
			_visualData->SetAnimation("Run");
		}
	}
	else if (!willMove && _isMoving)
	{
		_isMoving = false;
		_isRunning = false;
		_visualData->SetAnimation("Idle");

	}

}

void Player::UpdateCamera()
{
	if (_isHidden)
	{
		return;
	}

	int x, y;
	GetPosition(x, y);
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
	if (_camera->X > _map->GetLevelWidth() - _camera->Width)
	{
		_camera->X = _map->GetLevelWidth() - _camera->Width;
	}
	if (_camera->Y > _map->GetLevelHeight() - _camera->Height)
	{
		_camera->Y = _map->GetLevelHeight() - _camera->Height;
	}
}


void Player::SetIsHidden(bool value)
{
	_isHidden = value;
	_visualData->IsHidden = value;
}

void Player::GetPosition(int &x, int &y)
{
	x = Transform->X + (Transform->Width*0.5);
	y = Transform->Y + (Transform->Height*0.5);
}