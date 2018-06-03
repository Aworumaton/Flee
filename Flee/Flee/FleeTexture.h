#ifndef FLEE_TEXTURE_H
#define FLEE_TEXTURE_H

#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include "Constants.h"
#include "FleeLibrary.h"


//Texture wrapper class
class FleeTexture
{
public:
	//Initializes variables
	FleeTexture(SDL_Renderer * renderer);

	//Deallocates memory
	~FleeTexture();

	//Loads image at specified path
	bool LoadFromFile(std::string path);

#ifdef _SDL_TTF_H
	//Creates image from font string
	bool LoadFromRenderedText(std::string textureText, SDL_Color textColor);
#endif

	//Deallocates texture
	void Free();

	//Set color modulation
	void SetColor(Uint8 red, Uint8 green, Uint8 blue);

	//Set blending
	void SetBlendMode(SDL_BlendMode blending);

	//Set alpha modulation
	void SetAlpha(Uint8 alpha);

	//Renders texture at given point
	void Render(int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

	//Renders texture at given point
	void Render(FleeTransform * renderClip, FleeTransform * worldClip);

	//Gets image dimensions
	int GetWidth();
	int GetHeight();

private:
	//The window renderer
	SDL_Renderer * _renderer = NULL;

	//The actual hardware texture
	SDL_Texture * _texture;

	//Image dimensions
	int _width;
	int _height;
};

#endif