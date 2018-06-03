#ifndef Player_H
#define Player_H
#include <SDL.h>
#include <SDL_image.h>
#include "math.h"
#include "FleeLibrary.h"
#include "GameEntity.h"
#include "Input.h"
#include "Constants.h"
#include "Scene.h"
#include "AnimationManager.h"


class Player : public Character
{
public:
	Player(Scene* map, Main_Agent_Controls* controls, FleeTransform* camera);
	~Player();

	void Tick(int dt);

private:
	const float DEFAULT_VELOCITY = 64.0f /1000.0f;
	const float SPRINT_MULTIPTLIER = 3.0f;
	Scene * _map;
	FleeTransform * _camera;
	int _actionRadius;
	Main_Agent_Controls * _controls;
	bool _isHidden;
	bool _isMoving;
	bool _isRunning;
	
	void Move(int dt);
	void UpdateCamera();

	void SetIsHidden(bool value);
	void GetPosition(int &x, int &y);
};

#endif