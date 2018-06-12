/*
*	Author: Omer Sari
*/
#ifndef Enemy_H
#define Enemy_H
#include "Constants.h"
#include "Scene.h"
#include "GameEntity.h"
#include "PathFinder.h"
#include "AnimationManager.h"

class Enemy : public Character
{
public:
	Enemy(Scene* map, NavigationGridMap* navMap);
	~Enemy();

	void SetTarget(FleeTransform* target);
	void Tick(int dt);
private:
	const float DEFAULT_VELOCITY = 96.0f / 1000.0f;
	const float SPRINT_MULTIPTLIER = 3.0f;
	Scene * _map;
	int _actionRadius;
	bool _isMoving;
	bool _isRunning;

	void Move(int dt);
	void GetPositionOf(int &x, int &y, FleeTransform* target);

	PathFinder* _pathFinder;
};


#endif