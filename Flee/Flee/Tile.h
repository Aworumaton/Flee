#ifndef Tile_H
#define Tile_h
#include "FleeRenderer.h"

class Tile
{
public:
	const static int TILE_WIDTH = 32;
	const static int TILE_HEIGHT = 32;
	Tile(int type)
	{
		switch (type)
		{
		case 0:
			_visualData = new SpriteData("Tile_ground");
			_isWall = false;
			break;
		case 1:
			_visualData = new SpriteData("Tile_wall");
			_isWall = true;
			break;
		}

		FleeRenderer::Register(_visualData, Constants::VisualLayers::GroundLayer);
	};

	bool IsObstacle()
	{
		return _isWall;
	};

	bool IsWall()
	{
		return _isWall;
	};


	FleeTransform* Transform()
	{
		return _visualData->Transform;
	};

private:
	bool _isWall;
	SpriteData* _visualData;
};



#endif