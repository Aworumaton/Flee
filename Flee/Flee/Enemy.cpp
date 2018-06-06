#pragma once
#include "Enemy.h"

Enemy::Enemy(Scene* map)
{
	_map = map;

	_visualData = AnimationManager::CreateAnimationsOf("Player", Constants::VisualLayers::DynamicObjectsLayer);
	_visualData->SetAnimation("Idle");
	_isMoving = false;
	_isRunning = false;

	Transform = _visualData->Transform;
	_actionRadius = 2 * (0.5*(Transform->Width + Transform->Height));

	Transform->X = 450;
	Transform->Y = 250;
	//mBox.w = _visual->getBox().w;
	//mBox.h = _visual->getBox().h;
}

Enemy::~Enemy()
{
	Character::~Character();
}

void Enemy::Tick(int dt)
{
	Move(dt);
}

void Enemy::Move(int dt)
{

	int targetX;
	int targetY;
	GetPositionOf(targetX, targetY, _target);

	int sourceX;
	int sourceY;
	GetPositionOf(sourceX, sourceY, Transform);

	bool willMove = false;
	if (targetX != sourceX || targetY != sourceY)
	{
		int vel = 0;
		vel = DEFAULT_VELOCITY * dt;

		float mVelY = 0;
		float mVelX = 0;
		mVelX = (targetX - sourceX);
		mVelY = (targetY - sourceY);

		//double targetTotalVel = sqrt((mVelX*mVelX) + (mVelY*mVelY)) / (DEFAULT_VELOCITY * dt);
		//mVelX = (int)(mVelX / targetTotalVel);
		//mVelY = (int)(mVelY / targetTotalVel);

		float degrees = atan2f(mVelY,  mVelX);
		
		mVelX = cosf(degrees)*DEFAULT_VELOCITY * dt;
		mVelY = sinf(degrees)*DEFAULT_VELOCITY * dt;
		printf("vel x:%f\t\ty:%f\n", (cosf(degrees)*DEFAULT_VELOCITY * dt), (sinf(degrees)*DEFAULT_VELOCITY * dt));
		printf("vel x:%f\t\ty:%f\n", roundf((cosf(degrees)*DEFAULT_VELOCITY * dt)), roundf((sinf(degrees)*DEFAULT_VELOCITY * dt)));

		int oldX = Transform->X;
		int oldY = Transform->Y;

		Transform->X += roundf( mVelX);

		if (Transform->X < 0)
		{
			Transform->X = 0;
		}
		else if (Transform->X + Transform->Width > _map->GetLevelWidth())
		{
			Transform->X = _map->GetLevelWidth() - Transform->Width;
		}
		else if (_map->TouchesWalls(Transform))
		{
			//move back
			Transform->X = oldX;
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
		else if (_map->TouchesWalls(Transform))
		{
			//move back
			Transform->Y = oldY;
		}

		Transform->Rotation = (int)(180.0f / M_PI * atan2(mVelY, mVelX));

		//normalize
		Transform->Rotation = (450 + (int)Transform->Rotation) % 360;


		willMove = oldX != Transform->X || oldY != Transform->Y;

	}
	if (willMove && !_isMoving)
	{
		_isMoving = true;
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
	_target = target;
}

void Enemy::GetPositionOf(int &x, int &y, FleeTransform* target)
{
	x = target->X + (target->Width*0.5);
	y = target->Y + (target->Height*0.5);
}