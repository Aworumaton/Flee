/*
*	Author: Omer Sari
*/
#ifndef Scene_H
#define Scene_H

#include <SDL.h>
#include <fstream>
#include <string>
#include "AnimationManager.h"
#include "Tile.h"
#include "GameEntity.h"


class Scene
{
public:

	Scene();
	~Scene();

	bool Initialize();
	bool IsBlocked(FleeTransform* sourceTransform);

	void Tick(int dt);

	int GetLevelWidth();
	int GetLevelHeight();

	GameObject* GetFirstObjetUnder(SDL_Point point);

private:
	FleeList<Tile*> _mapLayout;
	FleeList<GameObject*> _objects;
	int _levelWidth;
	int _levelHeight;

	//Sets tiles from tile map
	bool Read();
};

#endif