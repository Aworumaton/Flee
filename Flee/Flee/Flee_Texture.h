#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include "Constants.h"

//Texture wrapper class
class Flee_Texture
{
public:
	//Initializes variables
	Flee_Texture();
	Flee_Texture(SDL_Renderer* renderer);

	//Deallocates memory
	~Flee_Texture();

	//Loads image at specified path
	bool loadFromFile(std::string path);

	//Renders texture at given point
	void render(int x, int y, SDL_Rect* clip = NULL);

	//Gets image dimensions
	int getWidth();
	int getHeight();

private:
	//The actual hardware texture
	SDL_Texture * _texture;

	//Image dimensions
	int _width;
	int _height;
	SDL_Renderer* _renderer;
};