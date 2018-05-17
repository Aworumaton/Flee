#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include "Constants.h"
#include "Flee_Texture.cpp"

//Texture wrapper class
class Texture_Manager
{
public:
	//Initializes variables
	Texture_Manager(SDL_Window* window);

	//Deallocates memory
	~Texture_Manager();

	//Loads image at specified path
	bool loadFromFile(std::string path);

	//Deallocates texture
	void free();

	//Renders texture at given point
	void render(int x, int y, SDL_Rect* clip = NULL);

	//Gets image dimensions
	int getWidth();
	int getHeight();

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

	void close();
	bool loadMedia();
};

Texture_Manager::Texture_Manager(SDL_Window* window)
{
	_window = window;

	//Set texture filtering to linear
	if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
	{
		printf("Warning: Linear texture filtering not enabled!");
	}

	_renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);

	if (_renderer == NULL)
	{
		printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
	}
	else
	{
		//Initialize renderer color
		SDL_SetRenderDrawColor(_renderer, 0xFF, 0xFF, 0xFF, 0xFF);

		//Initialize PNG loading
		int imgFlags = IMG_INIT_PNG;
		if (!(IMG_Init(imgFlags) & imgFlags))
		{
			printf("SDL_image could not initialize! SDL_mage Error: %s\n", IMG_GetError());
		}
	}


	//Clear screen
	SDL_SetRenderDrawColor(_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(_renderer);

	//Render top left sprite
	gSpriteSheetTexture.render(0, 0, &gSpriteClips[0]);

	//Render top right sprite
	gSpriteSheetTexture.render(SCREEN_WIDTH - gSpriteClips[1].w, 0, &gSpriteClips[1]);

	//Render bottom left sprite
	gSpriteSheetTexture.render(0, SCREEN_HEIGHT - gSpriteClips[2].h, &gSpriteClips[2]);

	//Render bottom right sprite
	gSpriteSheetTexture.render(SCREEN_WIDTH - gSpriteClips[3].w, SCREEN_HEIGHT - gSpriteClips[3].h, &gSpriteClips[3]);

	//Update screen
	SDL_RenderPresent(_renderer);
}

bool Texture_Manager::loadMedia()
{
	//Loading success flag
	bool success = true;

	//Load sprite sheet texture
	if (!gSpriteSheetTexture.loadFromFile("11_clip_rendering_and_sprite_sheets/dots.png"))
	{
		printf("Failed to load sprite sheet texture!\n");
		success = false;
	}
	else
	{
		//Set top left sprite
		gSpriteClips[0].x = 0;
		gSpriteClips[0].y = 0;
		gSpriteClips[0].w = 100;
		gSpriteClips[0].h = 100;

		//Set top right sprite
		gSpriteClips[1].x = 100;
		gSpriteClips[1].y = 0;
		gSpriteClips[1].w = 100;
		gSpriteClips[1].h = 100;

		//Set bottom left sprite
		gSpriteClips[2].x = 0;
		gSpriteClips[2].y = 100;
		gSpriteClips[2].w = 100;
		gSpriteClips[2].h = 100;

		//Set bottom right sprite
		gSpriteClips[3].x = 100;
		gSpriteClips[3].y = 100;
		gSpriteClips[3].w = 100;
		gSpriteClips[3].h = 100;
	}

	return success;
}

void Texture_Manager::close()
{
	//Free loaded images
	delete(&gSpriteSheetTexture);

	//Destroy window
	SDL_DestroyRenderer(_renderer);
	SDL_DestroyWindow(_window);
	_window = NULL;
	_renderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}
