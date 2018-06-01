#ifndef FLEE_TEXTURE_H
#define FLEE_TEXTURE_H

#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include "Constants.h"
#include "FleeLibrary.h"


//Texture wrapper class
class Flee_Texture
{
public:
	//Initializes variables
	Flee_Texture(SDL_Renderer * renderer);

	//Deallocates memory
	~Flee_Texture();

	//Loads image at specified path
	bool loadFromFile(std::string path);

#ifdef _SDL_TTF_H
	//Creates image from font string
	bool loadFromRenderedText(std::string textureText, SDL_Color textColor);
#endif

	//Deallocates texture
	void free();

	//Set color modulation
	void setColor(Uint8 red, Uint8 green, Uint8 blue);

	//Set blending
	void setBlendMode(SDL_BlendMode blending);

	//Set alpha modulation
	void setAlpha(Uint8 alpha);

	//Renders texture at given point
	void render(int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

	//Renders texture at given point
	void Render(FleeTransform * renderClip, FleeTransform * worldClip);

	//Gets image dimensions
	int getWidth();
	int getHeight();

private:
	//The window renderer
	SDL_Renderer * gRenderer = NULL;

	//The actual hardware texture
	SDL_Texture * mTexture;

	//Image dimensions
	int mWidth;
	int mHeight;
};

#endif