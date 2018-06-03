#ifndef FleeRenderer_H
#define FleeRenderer_H

#include <SDL_image.h>
#include <string>
#include <stdio.h>
#include <fstream>
#include <iostream>
#include "Constants.h"
#include "FleeLibrary.h"
#include "FleeList.h"
#include "Flee_Texture.h"

struct Sprite
{
	std::string Id;
	FleeTransform Transform; //spritesheet transform
	GameEntityFlags* Flags;		
};

class FleeRenderer
{

public:
	static bool Initialize();
	static void Free();

	static bool Register(SpriteData* spriteData, Constants::VisualLayers layerIndex);
	//static Flee_Animated_Sprite_Part* Create_Animated_Sprite(std::string sprite_id);
	
	static void Tick(float dt);

	static FleeTransform* GetCamera();
private:
	const static int SCREEN_WIDTH;
	const static int SCREEN_HEIGHT;


	FleeRenderer(bool& success);
	~FleeRenderer();

	bool RegisterSprite(SpriteData* spriteData, Constants::VisualLayers layerIndex);
	Sprite* GetSprite(std::string id);
	void RenderTick(float dt);


	struct SpriteDataSpritePair
	{
		Sprite* Sprite;
		SpriteData* SpriteData;
	};

	static FleeRenderer* _current;

	FleeList<FleeList<SpriteDataSpritePair*>*> Layers;
	FleeList<Sprite*> _sprites;
	Flee_Texture* _spriteSheet;
	FleeTransform* _camera;
	SDL_Window * _window;
	SDL_Renderer* _renderer;
	SDL_Surface* _screen_surface;
	


	bool ReadSprites();
};

#endif