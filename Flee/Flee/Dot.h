#ifndef DOT_H
#define DOT_H
#include <SDL.h>
#include <SDL_image.h>
#include "math.h"
#include "Flee_Texture.h"
#include "Input.h"
#include "Constants.h"
#include "Map_Manager.h"

//The dot that will move around on the screen
class Dot
{
public:
	//Initializes the variables
	Dot(SDL_Renderer* renderer, Map_Manager* map, Main_Agent_Controls* controls, SDL_Rect* camera);
	~Dot();

	//Moves the dot and check collision against tiles
	void move();

	//Centers the camera over the dot
	void Update_Camera();

	//Shows the dot on the screen
	void render();

private:
	SDL_Rect * _camera;
	//The dimensions of the dot
	const int DOT_WIDTH = 20;
	const int DOT_HEIGHT = 20;

	//Default axis velocity of the dot
	const int DEFAULT_DOT_VEL = 20;
	//Maximum axis velocity of the dot
	const int MAX_DOT_VEL = 2;

	int _rotation;
	Flee_Texture * gDotTexture;
	Main_Agent_Controls * _controls;
	//Collision box of the dot
	SDL_Rect mBox; 
	Map_Manager * _map;

};

#endif