#ifndef Map_Manager_H
#define Map_Manager_H

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

	bool TouchesWalls(FleeTransform* sourceTransform);

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