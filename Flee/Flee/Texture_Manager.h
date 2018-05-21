#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#include <SDL_image.h>
#include <string>
#include <stdio.h>
#include <fstream>
#include <iostream>
#include "Flee_Sprite_Part.h"
#include "Flee_Animated_Sprite_Part.h"
#include "Flee_Texture.h"

class Texture_Manager
{

public:
	static bool Initialize(SDL_Renderer* renderer);
	static void Free();

	static Flee_Sprite_Part* Create_Sprite(std::string sprite_id);
	static Flee_Animated_Sprite_Part* Create_Animated_Sprite(std::string sprite_id);
	
private:
	struct Flee_Sprite
	{
		std::string string_id;
		unsigned int flags;
		SDL_Rect bounds;
	};

	struct Flee_Animated_Sprite
	{
		std::string string_id;
		int animation_frame_count;
		Flee_Sprite** animation_targets;
	};


	Texture_Manager();
	~Texture_Manager();
	
	static Texture_Manager* _current;

	int _sprite_count;
	int _animated_sprite_count;

	Flee_Sprite* _tile_clips;
	Flee_Animated_Sprite* _animations;
	Flee_Sprite_Part * * _sprite_parts;
	Flee_Texture* _sprite_sheet;

	bool Read_Sprites();
	bool Read_Animations();
	Flee_Sprite* Get_Flee_Sprite(std::string string_id);
};

#endif