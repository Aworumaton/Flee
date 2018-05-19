#ifndef DOT_H
#define DOT_H
#include <SDL.h>
#include <SDL_image.h>
#include "Flee_Texture.h"
#include "Input.h"
#include "Constants.h"
#include "Map_Manager.h"

//The dot that will move around on the screen
class Dot
{
public:
	//Initializes the variables
	Dot(SDL_Renderer* renderer, Map_Manager* map, Main_Agent_Controls* controls);
	~Dot();

	//Moves the dot and check collision against tiles
	void move();

	//Centers the camera over the dot
	void setCamera(SDL_Rect& camera);

	//Shows the dot on the screen
	void render(SDL_Rect& camera);

private:
	//The dimensions of the dot
	const int DOT_WIDTH = 20;
	const int DOT_HEIGHT = 20;

	//Default axis velocity of the dot
	const int DEFAULT_DOT_VEL = 20;
	//Maximum axis velocity of the dot
	const int MAX_DOT_VEL = 2;

	Flee_Texture * gDotTexture;
	Main_Agent_Controls * _controls;
	//Collision box of the dot
	SDL_Rect mBox; 
	Map_Manager * _map;

};

#endif