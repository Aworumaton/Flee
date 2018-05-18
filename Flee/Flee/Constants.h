#ifndef CONSTANTS_H
#define CONSTANTS_H


namespace Constants
{
	//Screen dimension constants
	const int SCREEN_WIDTH = 800;
	const int SCREEN_HEIGHT = 600;

	const int TILE_HEIGHT = 80;
	const int TILE_WIDTH = 80;

	const int LEVEL_WIDTH = 1280;
	const int LEVEL_HEIGHT = 960;


	const int TOTAL_TILES = 192;
	const int TOTAL_TILE_SPRITES = 12;


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

	enum Tile_Type
	{
		Invalid = -1,
		TILE_RED = 0,
		TILE_GREEN = 1,
		TILE_BLUE = 2,
		TILE_CENTER = 3,
		TILE_TOP = 4,
		TILE_TOPRIGHT = 5,
		TILE_RIGHT = 6,
		TILE_BOTTOMRIGHT = 7,
		TILE_BOTTOM = 8,
		TILE_BOTTOMLEFT = 9,
		TILE_LEFT = 10,
		TILE_TOPLEFT = 11,
		Count = 12
	};
}

#endif