#pragma once
#include "Flee_Texture.h"



Flee_Texture::Flee_Texture()
{

}
Flee_Texture::Flee_Texture(SDL_Renderer* renderer)
{
	_renderer = renderer;
	//Initialize
	_texture = NULL;
	_width = 0;
	_height = 0;
}

Flee_Texture::~Flee_Texture()
{
	if (_texture != NULL)
	{
		SDL_DestroyTexture(_texture);
		_texture = NULL;
		_width = 0;
		_height = 0;
	}
}

bool Flee_Texture::loadFromFile(std::string path)
{
	//Get rid of preexisting texture
	if (_texture != NULL)
	{

		printf("image already loaded!");
		return false;
	}

	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	}
	else
	{
		//Color key image
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));

		//Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(_renderer, loadedSurface);
		if (newTexture == NULL)
		{
			printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}
		else
		{
			//Get image dimensions
			_width = loadedSurface->w;
			_height = loadedSurface->h;
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	//Return success
	_texture = newTexture;
	return _texture != NULL;
}

void Flee_Texture::render(int x, int y, SDL_Rect* clip)
{
	//Set rendering space and render to screen
	SDL_Rect renderQuad = { x, y, _width, _height };

	//Set clip rendering dimensions
	if (clip != NULL)
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	//Render to screen
	SDL_RenderCopy(_renderer, _texture, clip, &renderQuad);
}

int Flee_Texture::getWidth()
{
	return _width;
}

int Flee_Texture::getHeight()
{
	return _height;
}
