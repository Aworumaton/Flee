#ifndef NavigationGridMap_H
#define NavigationGridMap_H
#include "Scene.h"
#include "GameEntity.h"
#include "AnimationManager.h"


class NavigationGridBlock
{
public:
	NavigationGridBlock(int x, int y) : X(x), Y(y)
	{
		DebugAnimation = AnimationManager::CreateAnimationsOf("DebugRect", Constants::VisualLayers::UserInterfaceLayer);
		DebugAnimation->Transform->X = x + Character::Size/2;
		DebugAnimation->Transform->Y = y + Character::Size/2;
	};

	NavigationGridBlock() : X(0), Y(0)
	{	};

	~NavigationGridBlock()
	{

	};
	const int X;
	const int Y;
	bool IsBlocked;
	AnimationData* DebugAnimation;
private:
};


class NavigationGridMap
{
public:
	NavigationGridMap() 
	{
	
	};

	~NavigationGridMap()
	{

	};
	
	bool Initialize(Scene* scene)
	{
		_width = ceil(1.0 * scene->GetLevelWidth() / Character::Size);
		_height = ceil(1.0 * scene->GetLevelHeight() / Character::Size);
		
	
			
		_grid = new NavigationGridBlock**[_width];
		for (int i = 0; i < _width; i++)
		{
			_grid[i] = new NavigationGridBlock*[_height];
		}
	
		FleeTransform curBlock;
		curBlock.Width = Character::Size;
		curBlock.Height = Character::Size;
	
		for (int i = 0; i < _width; i++)
		{
			for (int j = 0; j < _height; j++)
			{
				curBlock.X = i * Character::Size;// +Character::Size / 2;
				curBlock.Y = j * Character::Size;// +Character::Size / 2;
				_grid[i][j] = new NavigationGridBlock(curBlock.X, curBlock.Y);
				_grid[i][j]->IsBlocked = scene->IsBlocked(&curBlock);
			}
		}
		return true;
	};

	int GridSize()
	{
		return _width * _height;
	}

	int GridWidth()
	{
		return _width;
	}

	int GridHeight()
	{
		return _height;
	}

	NavigationGridBlock* GetBlockAt(int x, int y)
	{
		if (x < _width && x >= 0 && y < _height && y >= 0)
		{
			return _grid[x][y];
		}
		return nullptr;
	}

	int GetRealCostSquaredBetween(NavigationGridBlock* a, NavigationGridBlock* b)
	{
		//handle closed doors and other movement slowing effects later
		int dX = a->X - b->X;
		int dY = a->Y - b->Y;

		return (dX * dX) + (dY * dY);
	}

private :
	NavigationGridBlock*** _grid;
	int _width;
	int _height;
};


#endif