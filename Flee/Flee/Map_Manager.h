#ifndef Map_Manager_H
#define Map_Manager_H

#include <SDL.h>
#include <fstream>
#include <string>
#include "Texture_Manager.h"
#include "Flee_Sprite_Part.h"
#include "Flee_Animated_Sprite_Part.h"
#include "Flee_Interactable_Object.h"


class Map_Manager
{
public:
	
	Map_Manager(SDL_Renderer* renderer);
	~Map_Manager();

	void Render(SDL_Rect &camera);

	bool touches_walls(SDL_Rect box);

	//The window renderer
	SDL_Renderer* _renderer = NULL;

	void Tick(int dt);

	int Get_Level_Width();
	int Get_Level_Height();

	Flee_Interactable_Object* Get_First_Objet_Under(SDL_Point point);

private:

	Flee_Sprite_Part * * _tileSet;
	Flee_Interactable_Object** _objects;

	int _total_tiles;
	int _total_objects;

	int _level_width;
	int _level_height;

	//Sets tiles from tile map
	bool Read();
};

#endif