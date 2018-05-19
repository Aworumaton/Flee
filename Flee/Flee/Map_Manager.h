#ifndef Map_Manager_H
#define Map_Manager_H

#include <SDL.h>
#include <fstream>
#include "Flee_Tile.h"


class Map_Manager
{
public:
	
	Map_Manager(SDL_Renderer* renderer);
	~Map_Manager();

	void Render(SDL_Rect &camera);

	bool touches_walls(SDL_Rect box);
	SDL_Rect gTileClips[Constants::Tile_Type::Count];

	//The window renderer
	SDL_Renderer* _renderer = NULL;


	//Frees media and shuts down SDL
	void close(Flee_Tile* tiles[]);

	Flee_Tile** _tileSet;

	int Get_Level_Width();
	int Get_Level_Height();

private:
	int _total_tiles;

	int _level_width;
	int _level_height;

	int _tile_height;
	int _tile_width;

	//Sets tiles from tile map
	bool setTiles(Flee_Tile *tiles[]);
};

#endif