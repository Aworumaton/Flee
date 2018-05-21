#ifndef Flee_Sprite_Part_Base_H
#define Flee_Sprite_Part_Base_H
#include <SDL.h>


class Flee_Sprite_Part_Base
{
public:
	virtual void Render(SDL_Rect& camera, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE) = 0;
	virtual void Set_Position(int x, int y) = 0;
	//Get the collision box
	virtual SDL_Rect getBox() = 0;

};


#endif