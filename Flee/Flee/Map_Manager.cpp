#include "Map_Manager.h"

void Map_Manager::close(Flee_Tile* tiles[])
{
	//Deallocate tiles
	for (int i = 0; i < _total_tiles; ++i)
	{
		if (tiles[i] == NULL)
		{
			delete tiles[i];
			tiles[i] = NULL;
		}
	}

	_renderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
}

bool Map_Manager::setTiles(Flee_Tile* tiles[])
{
	//Success flag
	bool tilesLoaded = true;

	//The tile offsets
	int x = 0, y = 0;

	//Open the map
	std::ifstream map("Resources/lazy.map");

	//If the map couldn't be loaded
	if (!map.is_open())
	{
		printf("Unable to load map file!\n");
		tilesLoaded = false;
	}
	else
	{
		//Initialize the tiles
		for (int i = 0; i < _total_tiles; ++i)
		{
			//Determines what kind of tile will be made
			int tileType = -1;

			//Read tile from map file
			map >> tileType;

			//If the was a problem in reading the map
			if (map.fail())
			{
				//Stop loading map
				printf("Error loading map: Unexpected end of file!\n");
				tilesLoaded = false;
				break;
			}

			//If the number is a valid tile number
			if ((tileType >= 0) && (tileType < Constants::Tile_Type::Count))
			{
				
				tiles[i] = new Flee_Tile(x, y, _tile_width, _tile_height, tileType, _renderer, &gTileClips[tileType]);
			}
			//If we don't recognize the tile type
			else
			{
				//Stop loading map
				printf("Error loading map: Invalid tile type at %d!\n", i);
				tilesLoaded = false;
				break;
			}

			//Move to next tile spot
			x += _tile_width;

			//If we've gone too far
			if (x >= _level_width)
			{
				//Move back
				x = 0;

				//Move to the next row
				y += _tile_height;
			}
		}

		//Clip the sprite sheet
		if (tilesLoaded)
		{
			gTileClips[Constants::Tile_Type::TILE_RED].x = 0;
			gTileClips[Constants::Tile_Type::TILE_RED].y = 0;
			gTileClips[Constants::Tile_Type::TILE_RED].w = _tile_width;
			gTileClips[Constants::Tile_Type::TILE_RED].h = _tile_height;
					   
			gTileClips[Constants::Tile_Type::TILE_GREEN].x = 0;
			gTileClips[Constants::Tile_Type::TILE_GREEN].y = 80;
			gTileClips[Constants::Tile_Type::TILE_GREEN].w = _tile_width;
			gTileClips[Constants::Tile_Type::TILE_GREEN].h = _tile_height;
					   
			gTileClips[Constants::Tile_Type::TILE_BLUE].x = 0;
			gTileClips[Constants::Tile_Type::TILE_BLUE].y = 160;
			gTileClips[Constants::Tile_Type::TILE_BLUE].w = _tile_width;
			gTileClips[Constants::Tile_Type::TILE_BLUE].h = _tile_height;
					   
			gTileClips[Constants::Tile_Type::TILE_TOPLEFT].x = 80;
			gTileClips[Constants::Tile_Type::TILE_TOPLEFT].y = 0;
			gTileClips[Constants::Tile_Type::TILE_TOPLEFT].w = _tile_width;
			gTileClips[Constants::Tile_Type::TILE_TOPLEFT].h = _tile_height;
					   
			gTileClips[Constants::Tile_Type::TILE_LEFT].x = 80;
			gTileClips[Constants::Tile_Type::TILE_LEFT].y = 80;
			gTileClips[Constants::Tile_Type::TILE_LEFT].w = _tile_width;
			gTileClips[Constants::Tile_Type::TILE_LEFT].h = _tile_height;
					   
			gTileClips[Constants::Tile_Type::TILE_BOTTOMLEFT].x = 80;
			gTileClips[Constants::Tile_Type::TILE_BOTTOMLEFT].y = 160;
			gTileClips[Constants::Tile_Type::TILE_BOTTOMLEFT].w = _tile_width;
			gTileClips[Constants::Tile_Type::TILE_BOTTOMLEFT].h = _tile_height;
					  
			gTileClips[Constants::Tile_Type::TILE_TOP].x = 160;
			gTileClips[Constants::Tile_Type::TILE_TOP].y = 0;
			gTileClips[Constants::Tile_Type::TILE_TOP].w = _tile_width;
			gTileClips[Constants::Tile_Type::TILE_TOP].h = _tile_height;
					  
			gTileClips[Constants::Tile_Type::TILE_CENTER].x = 160;
			gTileClips[Constants::Tile_Type::TILE_CENTER].y = 80;
			gTileClips[Constants::Tile_Type::TILE_CENTER].w = _tile_width;
			gTileClips[Constants::Tile_Type::TILE_CENTER].h = _tile_height;
				
			gTileClips[Constants::Tile_Type::TILE_BOTTOM].x = 160;
			gTileClips[Constants::Tile_Type::TILE_BOTTOM].y = 160;
			gTileClips[Constants::Tile_Type::TILE_BOTTOM].w = _tile_width;
			gTileClips[Constants::Tile_Type::TILE_BOTTOM].h = _tile_height;
					   
			gTileClips[Constants::Tile_Type::TILE_TOPRIGHT].x = 240;
			gTileClips[Constants::Tile_Type::TILE_TOPRIGHT].y = 0;
			gTileClips[Constants::Tile_Type::TILE_TOPRIGHT].w = _tile_width;
			gTileClips[Constants::Tile_Type::TILE_TOPRIGHT].h = _tile_height;
					  
			gTileClips[Constants::Tile_Type::TILE_RIGHT].x = 240;
			gTileClips[Constants::Tile_Type::TILE_RIGHT].y = 80;
			gTileClips[Constants::Tile_Type::TILE_RIGHT].w = _tile_width;
			gTileClips[Constants::Tile_Type::TILE_RIGHT].h = _tile_height;
					   
			gTileClips[Constants::Tile_Type::TILE_BOTTOMRIGHT].x = 240;
			gTileClips[Constants::Tile_Type::TILE_BOTTOMRIGHT].y = 160;
			gTileClips[Constants::Tile_Type::TILE_BOTTOMRIGHT].w = _tile_width;
			gTileClips[Constants::Tile_Type::TILE_BOTTOMRIGHT].h = _tile_height;
		}
	}

	//Close the file
	map.close();

	//If the map was loaded fine
	return tilesLoaded;
}


void Map_Manager::Render(SDL_Rect &camera)
{
	//Render level
	for (int i = 0; i < _total_tiles; ++i)
	{
		_tileSet[i]->render(camera);
	}

}

int Map_Manager::Get_Level_Width()
{
	return _level_width;
}
int Map_Manager::Get_Level_Height()
{
	return _level_height;
}

bool Map_Manager::touches_walls(SDL_Rect box)
{
	//Go through the tiles
	for (int i = 0; i < _total_tiles; ++i)
	{
		//If the tile is a wall type tile
		if ((_tileSet[i]->getType() >= Constants::Tile_Type::TILE_CENTER) && (_tileSet[i]->getType() <= Constants::Tile_Type::TILE_TOPLEFT))
		{
			//If the collision box touches the wall tile
			if (Constants::checkCollision(box, _tileSet[i]->getBox()))
			{
				return true;
			}
		}
	}

	//If no wall tiles were touched
	return false;
}

Map_Manager::~Map_Manager()
{
	close(_tileSet);
}

Map_Manager::Map_Manager(SDL_Renderer* renderer)
{
	_renderer = renderer;

	_tile_width = 80;
	_tile_height = 80;

	_level_width = 32 * _tile_width;
	_level_height = 24 * _tile_height;


	_total_tiles = 768;


	//Initialize PNG loading
	int imgFlags = IMG_INIT_PNG;
	if (_renderer == NULL)
	{
		printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
		return;
	}

	if(!(IMG_Init(imgFlags) & imgFlags))
	{
		printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
		return;
	}
	
	//Load the level tiles
	_tileSet = new Flee_Tile*[_total_tiles];
	if (!setTiles(_tileSet))
	{
		printf("Failed to load tile set!\n");
		return;
	}
}