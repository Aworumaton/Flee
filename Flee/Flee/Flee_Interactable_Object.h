#ifndef Flee_Interactable_Object_H
#define Flee_Interactable_Object_H
#include <SDL.h>
#include "Flee_Animated_Sprite_Part.h"

class Flee_Interactable_Object : Flee_Sprite_Part_Base
{
public:
	Flee_Interactable_Object(Flee_Animated_Sprite_Part* visual);
	bool Is_Door();
	bool Is_Obstruction();
	bool Is_Hiding_Place();

	void Tick(int dt);
	void OnAction();

	void Render(SDL_Rect& camera, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);
	void Set_Position(int x, int y);

	//Get the collision box
	SDL_Rect getBox();

private:
	Flee_Animated_Sprite_Part * _visual;

};
#endif