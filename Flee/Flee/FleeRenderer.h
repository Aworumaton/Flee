#ifndef FleeRenderer_H
#define FleeRenderer_H

#include <SDL_image.h>
#include <string>
#include <stdio.h>
#include <fstream>
#include <iostream>
#include "Constants.h"
#include "FleeTransform.h"
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
	FleeTransform Transform; //spritesheet transform
	unsigned int Flags;
};

class SpriteData
{
public:
	SpriteData(std::string id)
	{
		_id = id;
		IsHidden = false;
		Transform = new FleeTransform();
		Transform->Width = -1;
		Transform->Height = -1;
	};

	~SpriteData()
	{
		delete(Transform);
	}

	bool InitializeWith(Sprite* source)
	{
		if (source->Id != _id)
		{
			return false;
		}

		_isWall = (source->Flags & Sprite::FlagTypes::Wall) == Sprite::FlagTypes::Wall;

		if (Transform->Width < 0)
		{
			Transform->Width = source->Transform.Width;
		}

		if (Transform->Height < 0)
		{
			Transform->Height = source->Transform.Height;
		}


		return true;
	};

	FleeTransform* Transform; //World transform
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

	static bool Register(SpriteData* spriteData, int layerIndex);
	//static Flee_Animated_Sprite_Part* Create_Animated_Sprite(std::string sprite_id);
	
	static void Tick(float dt);

	static FleeTransform* GetCamera();
private:
	const static int SCREEN_WIDTH;
	const static int SCREEN_HEIGHT;


	FleeRenderer(bool& success);
	~FleeRenderer();

	bool RegisterSprite(SpriteData* spriteData, int layerIndex);
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
	


	FleeList<Sprite*>* ReadSprites();
};

#endif