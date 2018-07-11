/*
*	Author: Omer Sari
*/
#pragma once
#include "CharacterVision.h"

CharacterVision::CharacterVision(Scene * map, FleeTransform* sourceTransform, float visionDistance)
{
	_visionDistance = visionDistance + sqrt((sourceTransform->Height*sourceTransform->Height) + (sourceTransform->Width*sourceTransform->Width));
	_sourceTransform = sourceTransform;
	_map = map;
}

CharacterVision::~CharacterVision()
{
}

void CharacterVision::SetTarget(FleeTransform * target)
{
	_target = target;
	_targetRadius = sqrt((target->Height*target->Height) + (target->Width*target->Width));
}

FleeTransform* CharacterVision::GetTarget()
{
	return _target;
}

bool CharacterVision::IsTargetInVision()
{
	double aX = _sourceTransform->X + _sourceTransform->Width / 2.0;
	double aY = _sourceTransform->Y + _sourceTransform->Height / 2.0;

	double bX = _target->X + _target->Width / 2.0;
	double bY = _target->Y + _target->Height / 2.0;

	double dX = aX - bX;
	double dY = aY - bY;

	if (sqrt((dX*dX) + (dY*dY)) - _targetRadius > _visionDistance)
	{
		return false;
	}

	return true;
}

void CharacterVision::Tick(int dt)
{
}
