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

	void Tick();

private:
	const int DEFAULT_VELOCITY = 4;
	const int MAX_VELOCITY = 10;
	Scene * _map;
	FleeTransform * _camera;
	int _actionRadius;
	Main_Agent_Controls * _controls;
	bool _isHidden;
	bool _isMoving;
	
	void Move();
	void UpdateCamera();

	void SetIsHidden(bool value);
	void GetPosition(int &x, int &y);
};

#endif