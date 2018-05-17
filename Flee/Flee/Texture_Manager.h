#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include "Constants.h"
#include "Flee_Texture.h"

//Texture wrapper class
class Texture_Manager
{
public:
	//Initializes variables
	Texture_Manager();
	Texture_Manager(SDL_Window* window);

	//Deallocates memory
	~Texture_Manager();

	//Loads image at specified path
	bool loadMedia();

	//Deallocates texture
	void close();

private:
	//The actual hardware texture
	SDL_Texture * * mTexture;
	//SDL_Window* _window;

	//Image dimensions
	int mWidth;
	int mHeight;

	SDL_Window* _window;
	SDL_Renderer* _renderer;
	//Scene sprites
	SDL_Rect gSpriteClips[4];
	Flee_Texture gSpriteSheetTexture;
};

