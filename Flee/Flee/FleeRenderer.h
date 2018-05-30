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
	enum FlagTypes
	{
		None = 0b0000000000000000,
		Ground = 0b0000000000000001,
		Wall = 0b0000000000000010,
		Door = 0b0000000000000100,
		Hiding_Place = 0b0000000000001000,
	};

	std::string Id;
	Transform Transform; //spritesheet transform
	unsigned int Flags;
};

class SpriteData
{
public:
	SpriteData(std::string id)
	{
		_id = id;
		IsHidden = false;

		Transform.Width = -1;
		Transform.Height = -1;
	};

	bool InitializeWith(Sprite* source)
	{
		if (source->Id != _id)
		{
			return false;
		}

		_isWall = (source->Flags & Sprite::FlagTypes::Wall) == Sprite::FlagTypes::Wall;

		if (Transform.Width < 0)
		{
			Transform.Width = source->Transform.Width;
		}

		if (Transform.Height < 0)
		{
			Transform.Height = source->Transform.Height;
		}


		return true;
	};

	Transform Transform; //World transform
	bool IsHidden;

	bool IsWall()
	{
		return _isWall;
	};

	std::string Id()
	{
		return _id;
	};

private:
	std::string _id;
	bool _isWall;


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


	FleeRenderer(bool& success);
	~FleeRenderer();

	bool RegisterSprite(SpriteData* spriteData);
	Sprite* GetSprite(std::string id);
	void RenderTick(float dt);


	struct SpriteDataSpritePair
	{
		Sprite* Sprite;
		SpriteData* SpriteData;
	};

	static FleeRenderer* _current;

	FleeList<SpriteDataSpritePair*> SpriteDataSpriteList;
	FleeList<Sprite*> _sprites;
	Flee_Texture* _spriteSheet;
	Transform* _camera;
	SDL_Window * _window;
	SDL_Renderer* _renderer;
	SDL_Surface* _screen_surface;
	


	FleeList<Sprite*>* ReadSprites();
};

#endif