#ifndef DOT_H
#define DOT_H

#include <SDL.h>
#include <SDL_image.h>
#include "Flee_Texture.h"
#include "Flee_Tile.h"
#include "Input.h"
#include "Constants.h"

//The dot that will move around on the screen
class Dot
{
	Flee_Texture* gDotTexture;
public:
	//The dimensions of the dot
	static const int DOT_WIDTH = 20;
	static const int DOT_HEIGHT = 20;

	//Maximum axis velocity of the dot
	static const int DOT_VEL = 10;

	//Initializes the variables
	Dot(SDL_Renderer* renderer, Main_Agent_Controls* controls);
	Dot();
	~Dot();

	//Moves the dot and check collision against tiles
	void move(Flee_Tile *tiles[]);

	//Centers the camera over the dot
	void setCamera(SDL_Rect& camera);

	bool touchesWall(SDL_Rect box, Flee_Tile* tiles[]);

	//Shows the dot on the screen
	void render(SDL_Rect& camera);

private:
	Main_Agent_Controls * _controls;
	//Collision box of the dot
	SDL_Rect mBox;
};

#endif