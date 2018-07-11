/*
*	Author: Omer Sari
*/
#ifndef CharacterVision_H
#define CharacterVision_H
#include "Constants.h"
#include "Scene.h"
#include "GameEntity.h"

class CharacterVision : public Behaviour
{
public:
	CharacterVision(Scene* map, FleeTransform* sourceTransform, float visionDistance);
	~CharacterVision();

	void SetTarget(FleeTransform* target);
	FleeTransform* GetTarget();

	bool IsTargetInVision();
	void Tick(int dt);

private:
	double _visionDistance;
	double _targetRadius;
	Scene * _map;
	FleeTransform* _target;
	FleeTransform* _sourceTransform;
};


#endif