#ifndef NavigationGridMap_H
#define NavigationGridMap_H
#include "Scene.h"
#include "GameEntity.h"


class NavigationGridBlock
{
public:
	NavigationGridBlock(int x, int y) : X(x), Y(y)
	{
	};

	NavigationGridBlock() : X(0), Y(0)
	{	};

	~NavigationGridBlock()
	{

	};
	const int X;
	const int Y;
	bool IsBlocked;
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
		if (x < _width && x > 0 && y < _height && y > 0)
		{
			return _grid[x][y];
		}
		return nullptr;
	}
private :
	NavigationGridBlock*** _grid;
	int _width;
	int _height;
};


#endif