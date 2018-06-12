/*
*	Author: Omer Sari
*/
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
	FleeTexture(SDL_Renderer * renderer);
	~FleeTexture();

	bool LoadFromFile(std::string path);

	void Free();

	void SetColor(Uint8 red, Uint8 green, Uint8 blue);

	void SetBlendMode(SDL_BlendMode blending);

	void SetAlpha(Uint8 alpha);

	void Render(int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);
	void Render(FleeTransform * renderClip, FleeTransform * worldClip);

	int GetWidth();
	int GetHeight();

private:
	SDL_Renderer * _renderer = NULL;
	SDL_Texture * _texture;

	int _width;
	int _height;
};

#endif