#ifndef FleeRenderer_H
#define FleeRenderer_H

#include <SDL_image.h>
#include <string>
#include <stdio.h>
#include <fstream>
#include <iostream>
#include "Constants.h"
#include "Transform.h"
#include "FleeList.h"
#include "Flee_Sprite_Part.h"
#include "Flee_Animated_Sprite_Part.h"
#include "Flee_Texture.h"

struct Sprite
{
	std::string Id;
	Transform Transform; //spritesheet transform
	unsigned int Flags;
};
struct SpriteData
{
	std::string Id;
	Transform Transform; //World transform
	bool IsHidden;
};

class FleeRenderer
{

public:
	static bool Initialize();
	static void Free();

	static bool Register(SpriteData* spriteData);
	//static Flee_Animated_Sprite_Part* Create_Animated_Sprite(std::string sprite_id);
	
	static void Tick(float dt);

	static Transform* GetCamera();
private:
	const static int SCREEN_WIDTH;
	const static int SCREEN_HEIGHT;

	bool RegisterSprite(SpriteData* spriteData);
	Sprite* GetSprite(std::string id);
	void RenderTick(float dt);


	struct SpriteDataSpritePair
	{
		Sprite* Sprite;
		SpriteData* SpriteData;
	};


	FleeList<SpriteDataSpritePair*> SpriteDataSpriteList;
	FleeList<Sprite*> _sprites;
	Flee_Texture* _spriteSheet;
	Transform* _camera;
	SDL_Window * _window;
	SDL_Renderer* _renderer;
	SDL_Surface* _screen_surface;
	/*
	struct Flee_Sprite
	{
		std::string string_id;
		unsigned int flags;
		SDL_Rect bounds;
	};

	struct Flee_Animated_Sprite
	{
		std::string string_id;
		int animation_frame_count;
		Flee_Sprite** animation_targets;
	};
	*/

	FleeRenderer(bool& success);
	~FleeRenderer();
	
	static FleeRenderer* _current;


	FleeList<Sprite*>* ReadSprites();
	//bool Read_Animations();
	//Sprite* Get_Flee_Sprite(std::string string_id);
};

#endif