/*
*	Author: Omer Sari
*/
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
		DebugAnimation->Transform->X = x + (Character::Size - DebugAnimation->Transform->Width )/2;
		DebugAnimation->Transform->Y = y + (Character::Size - DebugAnimation->Transform->Height)/2;
	//	DebugAnimation->IsHidden = true;
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
	const int BlockSize;
public:
	NavigationGridMap() : BlockSize(Character::Size * 0.5)
	{
	
	};

	~NavigationGridMap()
	{

	};
	
	bool Initialize(Scene* scene)
	{
		_width = ceil(1.0 * scene->GetLevelWidth() / BlockSize);
		_height = ceil(1.0 * scene->GetLevelHeight() / BlockSize);
		
	
			
		_grid = new NavigationGridBlock**[_width];
		for (int i = 0; i < _width; i++)
		{
			_grid[i] = new NavigationGridBlock*[_height];
		}
	
		FleeTransform curBlock;
		curBlock.Width = Character::Size;
		curBlock.Height = Character::Size;

		for (int j = 0; j < _height; j++)
		{
			for (int i = 0; i < _width; i++)
			{
				curBlock.X = i * BlockSize;
				curBlock.Y = j * BlockSize;
				_grid[i][j] = new NavigationGridBlock(curBlock.X, curBlock.Y);
				_grid[i][j]->IsBlocked = scene->IsBlocked(&curBlock);
			}
		}
		
		//for (int j = 0; j < GridHeight(); j++)
		//{
		//	for (int i = 0; i < GridWidth(); i++)
		//	{
		//		if (_grid[i][j]->IsBlocked)
		//		{
		//			printf(" ");
		//		}
		//		else
		//		{
		//			printf("X");
		//		}
		//	}
		//	printf("\n");
		//}
		
		return true;
	};

	int GridWidth()
	{
		return _width;
	};

	int GridHeight()
	{
		return _height;
	};

	NavigationGridBlock* GetBlockAt(int x, int y)
	{
		if (x < _width && x >= 0 && y < _height && y >= 0)
		{
			return _grid[x][y];
		}
		return nullptr;
	};

	double GetRealCostBetween(NavigationGridBlock* a, NavigationGridBlock* b)
	{
		//handle closed doors and other movement slowing effects later
		int dX = a->X - b->X;
		int dY = a->Y - b->Y;

		return sqrt((dX * dX) + (dY * dY));
	};

	void GetNearestValidBlockAtPosition(FleeTransform* transform, int& x, int& y)
	{
		int xPadding = 0;
		int yPadding = 0;
		do
		{
			x = (transform->X + xPadding) / BlockSize;
			y = (transform->Y + yPadding) / BlockSize;
			xPadding += BlockSize;
			if (transform->Width < xPadding)
			{
				xPadding = 0;
				yPadding += BlockSize;
				if (transform->Height < yPadding)
				{
					return;
				}
			}
		} while (_grid[x][y]->IsBlocked);
	};

private :
	NavigationGridBlock*** _grid;
	int _width;
	int _height;
};


#endif