#ifndef DOT_H
#define DOT_H
#include <SDL.h>
#include <SDL_image.h>
#include "math.h"
#include "FleeLibrary.h"
#include "Flee_Animated_Sprite_Part.h"
#include "Flee_Interactable_Object.h"
#include "Input.h"
#include "Constants.h"
#include "Map_Manager.h"
#include "AnimationManager.h"

//The dot that will move around on the screen
class Dot
{
public:
	//Initializes the variables
	Dot(Map_Manager* map, Main_Agent_Controls* controls, FleeTransform* camera);
	~Dot();

	void Tick();

private:
	FleeTransform * _camera;

	FleeTransform* _transform;
	//SpriteData _visualData;

	AnimationData* _visualData;
	bool IsHidden;
	bool IsMoving;

	//Moves and check collision against tiles
	void Move();
	//Centers the camera over the dot
	void UpdateCamera();
	int _actionRadius;


	//Default axis velocity of the dot
	const int DEFAULT_DOT_VEL = 20;
	//Maximum axis velocity of the dot
	const int MAX_DOT_VEL = 2;

	int _animation_frame_rate = 100;
	int _animation_timer;

	//Flee_Animated_Sprite_Part * _visual;
	Main_Agent_Controls * _controls;
	Map_Manager * _map;

	void SetIsHidden(bool value)
	{
		IsHidden = value;
		_visualData->IsHidden = value;
	};

	void Get_Position(int &x, int &y)
	{
		x = _transform->X + (_transform->Width*0.5);
		y = _transform->Y + (_transform->Height*0.5);
	};

};

#endif