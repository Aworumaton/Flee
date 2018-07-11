/*
*	Author: Omer Sari
*/
#pragma once
#include "Enemy.h"

Enemy::Enemy(Scene* map, NavigationGridMap* navMap)
{
	_map = map;

	_visualData = AnimationManager::CreateAnimationsOf("Player", Constants::VisualLayers::DynamicObjectsLayer);
	_visualData->SetAnimation("Idle");
	_isMoving = false;
	_isRunning = false;

	Transform = _visualData->Transform;
	_actionRadius = 2 * (0.5*(Transform->Width + Transform->Height));

	//use a spawner later
	Transform->X = 450;
	Transform->Y = 250;

	_pathFinder = new PathFinder(Transform, navMap);
	_behaviours.Add(_pathFinder);

	_vision = new CharacterVision(_map, Transform, VISION_DISTANCE);
	_behaviours.Add(_vision);
}

Enemy::~Enemy()
{
	Character::~Character();
}

void Enemy::Tick(int dt)
{
	if (_vision->IsTargetInVision())
	{
		_pathFinder->SetTarget(_vision->GetTarget());
	}

	Character::Tick(dt);

	Move(dt);

}

void Enemy::Move(int dt)
{
	//Use collision detection to make movements smoother

	bool willMove = false;

	if (_pathFinder->WillMove())
	{
		int targetX = _pathFinder->LocalTarget.X + (_pathFinder->LocalTarget.Width*0.5);
		int targetY = _pathFinder->LocalTarget.Y + (_pathFinder->LocalTarget.Height*0.5);

		int sourceX = Transform->X;
		int sourceY = Transform->Y;

		if (targetX != sourceX || targetY != sourceY)
		{
			float vel = 0;
			vel = DEFAULT_VELOCITY * dt;

			double mVelX = (targetX - sourceX);
			double mVelY = (targetY - sourceY);


			double targetTotalDistance = sqrt((mVelX*mVelX) + (mVelY*mVelY));
			mVelX = mVelX / targetTotalDistance * vel;
			mVelY = mVelY / targetTotalDistance * vel;


			int oldX = Transform->X;
			int oldY = Transform->Y;

			Transform->X += round(mVelX);
			//If went too far to the top or down or touched a wall
			if (Transform->X < 0)
			{
				Transform->X = 0;
			}
			else if (Transform->X + Transform->Width > _map->GetLevelWidth())
			{
				Transform->X = _map->GetLevelWidth() - Transform->Width;
			}
			else if (_map->IsBlocked(Transform))
			{
				//move back
				Transform->X = oldX;

				mVelX = 0;

				int deltaY = targetY - sourceY;
				if (deltaY * deltaY < vel*vel)
				{
					mVelY = deltaY;
				}
				else
				{
					mVelY = vel;
					if (deltaY < 0)
					{
						mVelY *= -1.0;
					}
				}
			}

			Transform->Y += roundf(mVelY);

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

				mVelY = 0;

				int deltaX = targetX - sourceX;
				if (deltaX * deltaX < vel*vel)
				{
					mVelX = deltaX;
				}
				else
				{
					mVelX = vel;
					if (deltaX < 0)
					{
						mVelX *= -1.0;
					}
				}
				//try horizontal movement again
				Transform->X += round(mVelX);
				//If went too far to the top or down or touched a wall
				if (Transform->X < 0)
				{
					Transform->X = 0;
				}
				else if (Transform->X + Transform->Width > _map->GetLevelWidth())
				{
					Transform->X = _map->GetLevelWidth() - Transform->Width;
				}
				else if (_map->IsBlocked(Transform))
				{
					//move back
					Transform->X = oldX;
				}
			}

			Transform->Rotation = (int)(180.0f / M_PI * atan2(mVelY, mVelX));

			//normalize
			Transform->Rotation = (450 + (int)Transform->Rotation) % 360;


			willMove = oldX != Transform->X || oldY != Transform->Y;

		}
	}


	if (willMove && !_isMoving)
	{
		_isMoving = true;

		//add walking animations
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

void Enemy::SetTarget(FleeTransform* target)
{
	_vision->SetTarget(target);
}