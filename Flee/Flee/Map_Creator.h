#ifndef MAP_CREATOR_H
#define MAP_CREATOR_H

#include <SDL.h>
#include <assert.h>
#include <fstream>
#include "Flee_Tile.h"
#include "Dot.h"


class Map_Creator
{
public:
	Map_Creator(SDL_Renderer* renderer);
	~Map_Creator();

	void Render(SDL_Rect &camera);

	SDL_Rect gTileClips[Constants::Tile_Type::Count];

	//The window renderer
	SDL_Renderer* _renderer = NULL;


	//Frees media and shuts down SDL
	void close(Flee_Tile* tiles[]);

	Flee_Tile** _tileSet;
private:

	//Sets tiles from tile map
	bool setTiles(Flee_Tile *tiles[]);


};

#endif