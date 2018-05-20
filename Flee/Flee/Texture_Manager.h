#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#include <SDL_image.h>
#include <string>
#include <stdio.h>
#include "Flee_Sprite_Part.h"
#include "Flee_Texture.h"

class Texture_Manager
{
public:
	Texture_Manager(SDL_Renderer* renderer);
	~Texture_Manager();

	Flee_Sprite_Part* Create_Sprite_At(int x, int y, int tileType);

private:
	SDL_Rect* _tile_clips;
	Flee_Sprite_Part * * _sprite_parts;
	Flee_Texture* _sprite_sheet;

	void Read();
};

#endif
//#pragma once
//#include <SDL.h>
//#include <SDL_image.h>
//#include <stdio.h>
//#include <string>
//#include "Constants.h"
//#include "Flee_Texture.h"
//
////Texture wrapper class
//class Texture_Manager
//{
//public:
//	//Initializes variables
//	Texture_Manager();
//	Texture_Manager(SDL_Window* window);
//
//	//Deallocates memory
//	~Texture_Manager();
//
//	//Loads image at specified path
//	bool loadMedia();
//
//	//Deallocates texture
//	void close();
//
//private:
//	//The actual hardware texture
//	SDL_Texture * * mTexture;
//	//SDL_Window* _window;
//
//	//Image dimensions
//	int mWidth;
//	int mHeight;
//
//	SDL_Window* _window;
//	SDL_Renderer* _renderer;
//	//Scene sprites
//	SDL_Rect gSpriteClips[4];
//	Flee_Texture gSpriteSheetTexture;
//};

