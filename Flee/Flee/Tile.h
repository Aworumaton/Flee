#ifndef Tile_H
#define Tile_h
#include "FleeRenderer.h"

class Tile
{
public:
	const static int TILE_WIDTH = 32;
	const static int TILE_HEIGHT = 32;
	Tile(int type, int columnIndex, int rowIndex)
	{
		_columnIndex = columnIndex;
		_rowIndex = rowIndex;

		switch (type)
		{
		case 0:
			_isWall = false;
			break;
		case 1:
			_isWall = true;
			break;
		}

	};

	void InitializeWith(
			Tile* top,
			Tile* bottom,
			Tile* left,
			Tile* right)
	{
		_top = top;
		_left = left;
		_right = right;
		_bottom = bottom;


		if (_isWall)
		{
			std::string wallType = "Tile_wall_";
			bool everyAdjacentIsWall = true;
			if (_left != nullptr && !_left->_isWall)
			{
				wallType = wallType + "Left";
				everyAdjacentIsWall = false;
			}
			if (_right != nullptr && !_right->_isWall)
			{
				wallType = wallType + "Right";
				everyAdjacentIsWall = false;
			}

			if (_top != nullptr && !_top->_isWall)
			{
				wallType = wallType + "Top";
				everyAdjacentIsWall = false;
			}
			if (_bottom != nullptr && !_bottom->_isWall)
			{
				wallType = wallType + "Bottom";
				everyAdjacentIsWall = false;
			}

			if (everyAdjacentIsWall)
			{
				wallType = wallType + "Empty";
			}
			_visualData = new SpriteData(wallType);
		}
		else
		{
			_visualData = new SpriteData("Tile_ground");
		}
		FleeRenderer::Register(_visualData, Constants::VisualLayers::GroundLayer);
		_visualData->Transform->X = _columnIndex * TILE_WIDTH;
		_visualData->Transform->Y = _rowIndex * TILE_HEIGHT;

		if (_visualData == nullptr)
		{

		}
	}
	bool IsObstacle()
	{
		return _isWall;
	};

	FleeTransform* Transform()
	{
		return _visualData->Transform;
	}

private:
	bool _isWall;
	SpriteData* _visualData;

	Tile* _top;
	Tile* _left;
	Tile* _right;
	Tile* _bottom;

	int _columnIndex;
	int _rowIndex;
};



#endif