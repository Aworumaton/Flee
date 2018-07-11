/*
*	Author: Omer Sari
*/
#ifndef Enemy_H
#define Enemy_H
#include "Constants.h"
#include "Scene.h"
#include "GameEntity.h"
#include "PathFinder.h"
#include "CharacterVision.h"
#include "AnimationManager.h"

class Enemy : public Character
{
public:
	Enemy(Scene* map, NavigationGridMap* navMap);
	~Enemy();

	void SetTarget(FleeTransform* target);
	void Tick(int dt);
private:
	const float VISION_DISTANCE = 150.0f;
	const float DEFAULT_VELOCITY = 96.0f / 1000.0f;
	const float SPRINT_MULTIPTLIER = 3.0f;
	Scene * _map;
	int _actionRadius;
	bool _isMoving;
	bool _isRunning;

	void Move(int dt);

	PathFinder* _pathFinder;
	CharacterVision* _vision;
};


#endif