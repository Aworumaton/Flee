#ifndef NavigationGridMap_H
#define NavigationGridMap_H
#include "Scene.h"
#include "GameEntity.h"


class NavigationGridBlock
{
public:
	NavigationGridBlock()
	{

	};

	~NavigationGridBlock()
	{

	};

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
		int width = ceil(1.0 * scene->GetLevelWidth() / Character::Size);
		int height = ceil(1.0 * scene->GetLevelHeight() / Character::Size);
	
	
			
		_grid = new NavigationGridBlock*[width];
		for (int i = 0; i < width; i++)
		{
			_grid[i] = new NavigationGridBlock[height];
		}
	
		FleeTransform curBlock;
		curBlock.Width = Character::Size;
		curBlock.Height = Character::Size;
	
		for (int i = 0; i < width; i++)
		{
			for (int j = 0; j < height; j++)
			{
				curBlock.X = i * Character::Size;
				curBlock.Y = j * Character::Size;
				_grid[i][j] = NavigationGridBlock();
				_grid[i][j].IsBlocked = scene->IsBlocked(&curBlock);
			}
		}
		return true;
	};

private :
	NavigationGridBlock** _grid;
};


#endif