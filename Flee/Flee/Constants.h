#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <SDL.h>
#include "FleeLibrary.h"

//implement PhysicsManager and delete this
namespace Constants
{
	//Screen dimension constants
	enum VisualLayers
	{
		GroundLayer = 0,
		DynamicObjectsLayer = 1,
		UserInterfaceLayer = 2,
	};

	static bool checkCollision(SDL_Rect a, SDL_Rect b)
	{
		//The sides of the rectangles
		int leftA, leftB;
		int rightA, rightB;
		int topA, topB;
		int bottomA, bottomB;

		//Calculate the sides of rect A
		leftA = a.x;
		rightA = a.x + a.w;
		topA = a.y;
		bottomA = a.y + a.h;

		//Calculate the sides of rect B
		leftB = b.x;
		rightB = b.x + b.w;
		topB = b.y;
		bottomB = b.y + b.h;

		//If any of the sides from A are outside of B
		if (bottomA <= topB)
		{
			return false;
		}

		if (topA >= bottomB)
		{
			return false;
		}

		if (rightA <= leftB)
		{
			return false;
		}

		if (leftA >= rightB)
		{
			return false;
		}

		//If none of the sides from A are outside B
		return true;
	}

	static bool CheckCollision(FleeTransform* a, FleeTransform* b)
	{
		//The sides of the rectangles
		int leftA, leftB;
		int rightA, rightB;
		int topA, topB;
		int bottomA, bottomB;

		//Calculate the sides of rect A
		leftA = a->X;
		rightA = a->X + a->Width;
		topA = a->Y;
		bottomA = a->Y + a->Height;

		//Calculate the sides of rect B
		leftB = b->X;
		rightB = b->X + b->Width;
		topB = b->Y;
		bottomB = b->Y + b->Height;

		//If any of the sides from A are outside of B
		if (bottomA <= topB)
		{
			return false;
		}

		if (topA >= bottomB)
		{
			return false;
		}

		if (rightA <= leftB)
		{
			return false;
		}

		if (leftA >= rightB)
		{
			return false;
		}

		//If none of the sides from A are outside B
		return true;
	}

	static bool checkCollision(SDL_Rect a, SDL_Point b)
	{
		return (a.x <= b.x && b.x <= (a.x + a.w) && a.y <= b.y && b.y <= (a.y + a.h));
	}

	static bool checkCollision(FleeTransform a, SDL_Point b)
	{
		return (a.X <= b.x && b.x <= (a.X + a.Width) && a.Y <= b.y && b.y <= (a.Y + a.Height));
	}

	static double Get_Distance_Between(SDL_Point a, SDL_Point b)
	{
		int w = b.x - a.x;
		int h = b.y - a.y;
		return sqrt((w*w) + (h*h));
	}

}

#endif