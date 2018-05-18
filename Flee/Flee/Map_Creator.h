#ifndef MAP_CREATOR_H
#define MAP_CREATOR_H

#include <SDL.h>
#include <fstream>
#include "Flee_Tile.h"
#include "Dot.h"


class Map_Creator
{
public:
	Map_Creator(SDL_Window* window);

	SDL_Rect gTileClips[Constants::Tile_Type::Count];

	//The window we'll be rendering to
	SDL_Window* gWindow = NULL;

	//The window renderer
	SDL_Renderer* gRenderer = NULL;


	//Loads media
	bool loadMedia(Flee_Tile* tiles[]);

	//Frees media and shuts down SDL
	void close(Flee_Tile* tiles[]);

	//Box collision detector
	static bool checkCollision(SDL_Rect a, SDL_Rect b);

	//Sets tiles from tile map
	bool setTiles(Flee_Tile *tiles[]);

};

#endif