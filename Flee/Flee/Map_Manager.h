#ifndef Map_Manager_H
#define Map_Manager_H

#include <SDL.h>
#include <fstream>
#include <string>
#include "Texture_Manager.h"
#include "Flee_Sprite_Part.h"


class Map_Manager
{
public:
	
	Map_Manager(SDL_Renderer* renderer, Texture_Manager* texture_Manager);
	~Map_Manager();

	void Render(SDL_Rect &camera);

	bool touches_walls(SDL_Rect box);
	SDL_Rect gTileClips[Flee_Sprite_Part::Tile_Type::Count];

	//The window renderer
	SDL_Renderer* _renderer = NULL;


	Flee_Sprite_Part** _tileSet;

	int Get_Level_Width();
	int Get_Level_Height();

private:
	Texture_Manager * _texture_Manager;
	int _total_tiles;

	int _level_width;
	int _level_height;

	//Sets tiles from tile map
	bool Read_Tiles();
};

#endif