#pragma once
#include "FleeTexture.h"


FleeTexture::FleeTexture(SDL_Renderer * renderer)
{
	_renderer = renderer;

	_texture = NULL;
	_width = 0;
	_height = 0;
}

FleeTexture::~FleeTexture()
{
	Free();
}

bool FleeTexture::LoadFromFile(std::string path)
{
	//Get rid of preexisting texture
	Free();

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
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0xFF, 0, 0xFF)); //0xff00ff(magenta) substitudes the alpha channel

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

void FleeTexture::Free()
{
	if (_texture != NULL)
	{
		SDL_DestroyTexture(_texture);
		_texture = NULL;
		_width = 0;
		_height = 0;
	}
}

void FleeTexture::SetColor(Uint8 red, Uint8 green, Uint8 blue)
{
	//Modulate texture rgb
	SDL_SetTextureColorMod(_texture, red, green, blue);
}

void FleeTexture::SetBlendMode(SDL_BlendMode blending)
{
	//Set blending function
	SDL_SetTextureBlendMode(_texture, blending);
}

void FleeTexture::SetAlpha(Uint8 alpha)
{
	//Modulate texture alpha
	SDL_SetTextureAlphaMod(_texture, alpha);
}

void FleeTexture::Render(int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip)
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
	SDL_RenderCopyEx(_renderer, _texture, clip, &renderQuad, angle, center, flip);
}

void FleeTexture::Render(FleeTransform * renderClip, FleeTransform * worldClip)
{
	//Set rendering space and render to screen
	SDL_Rect renderRect = { renderClip->X, renderClip->Y, renderClip->Width, renderClip->Height };
	SDL_Rect worldRect = { worldClip->X, worldClip->Y,worldClip->Width, worldClip->Height };


	//Render to screen
	SDL_RenderCopyEx(_renderer, _texture, &renderRect, &worldRect, worldClip->Rotation, NULL, SDL_FLIP_NONE);
}

int FleeTexture::GetWidth()
{
	return _width;
}

int FleeTexture::GetHeight()
{
	return _height;
}
