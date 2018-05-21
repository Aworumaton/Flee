#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#include <SDL_image.h>
#include <string>
#include <stdio.h>
#include <fstream>
#include <iostream>
#include "Flee_Sprite_Part.h"
#include "Flee_Texture.h"
//#include "Flee_Sprite.h"

using namespace std;

class Texture_Manager
{

public:
	Texture_Manager(SDL_Renderer* renderer);
	~Texture_Manager();

	Flee_Sprite_Part* Create_Sprite(string sprite_id);
	int Get_Sprite_Count();

private:
	struct Flee_Sprite
	{
		string string_id;
		unsigned int flags;
		SDL_Rect bounds;
	};
	
	int _sprite_count;

	Flee_Sprite* _tile_clips;
	Flee_Sprite_Part * * _sprite_parts;
	Flee_Texture* _sprite_sheet;

	bool Read();
};

#endif