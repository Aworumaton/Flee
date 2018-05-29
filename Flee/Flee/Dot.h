#ifndef DOT_H
#define DOT_H
#include <SDL.h>
#include <SDL_image.h>
#include "math.h"
#include "Flee_Animated_Sprite_Part.h"
#include "Flee_Interactable_Object.h"
#include "Input.h"
#include "Constants.h"
#include "Map_Manager.h"

//The dot that will move around on the screen
class Dot
{
public:
	//Initializes the variables
	Dot(Map_Manager* map, Main_Agent_Controls* controls, Transform* camera);
	~Dot();

	void Update();
	
	//Centers the camera over the dot
	void Update_Camera();

	//Shows the dot on the screen
	void render();

	void Tick_Animations(int dt);
private:
	bool _is_Hidden;
	//Moves the dot and check collision against tiles
	void move();
	Transform * _camera;
	//The dimensions of the dot
	const int DOT_WIDTH = 40;
	const int DOT_HEIGHT = 40;

	const int ACTION_RADIUS = 2 * (0.5*(DOT_WIDTH+DOT_HEIGHT));
	//Default axis velocity of the dot
	const int DEFAULT_DOT_VEL = 20;
	//Maximum axis velocity of the dot
	const int MAX_DOT_VEL = 2;

	int _animation_frame_rate = 100;
	int _animation_timer;

	int _rotation;
	//Flee_Animated_Sprite_Part * _visual;
	Main_Agent_Controls * _controls;
	//Collision box of the dot
	SDL_Rect mBox; 
	Map_Manager * _map;

	void Get_Position(int &x, int &y)
	{
		x = mBox.x + (DOT_WIDTH*0.5);
		y = mBox.y + (DOT_HEIGHT*0.5);
	};

};

#endif