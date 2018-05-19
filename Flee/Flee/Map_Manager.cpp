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

bool Map_Manager::Read_Tiles()
{
	if (_tileSet != NULL)
	{

	}
	//Success flag
	bool tilesLoaded = true;

	//Open the map
	std::ifstream map("Resources/level_0.txt");

	//If the map couldn't be loaded
	if (!map.is_open())
	{
		printf("Unable to load map file!\n");
		tilesLoaded = false;
	}
	else
	{
		//Load the level tiles
		int tiles_capacity = 10 * 10;
		_tileSet = new Flee_Tile*[tiles_capacity];
		_total_tiles = 0;

		_level_width = 0;
		_level_height = 0;

		int cur_width = 0;
		int cur_height = 0;

		//Determines what kind of tile will be made
		int tileType = -1;
		int max_column_count = 1;
		int column_count = 1;
		int max_row_count = 1;
		//Initialize the tiles
		while (map >> tileType)
		{
			if (tiles_capacity == _total_tiles)
			{
				tiles_capacity = max_column_count * max_row_count * 1.8f;
				Flee_Tile** new_tile_set = new Flee_Tile*[tiles_capacity];
				for (int i = 0; i < _total_tiles; i++)
				{
					new_tile_set[i] = _tileSet[i];
				}
				delete(_tileSet);
				_tileSet = new_tile_set;
			}

			//If the number is a valid tile number
			if ((tileType >= 0) && (tileType < Constants::Tile_Type::Count))
			{
				_tileSet[_total_tiles] = new Flee_Tile(cur_width, cur_height, _tile_width, _tile_height, tileType, _renderer, &gTileClips[tileType]);
			}			
			else //If we don't recognize the tile type
			{
				//Stop loading map
				printf("Error loading map: Invalid tile type at %d!\n", _total_tiles);
				tilesLoaded = false;
				break;
			}

			if (map.peek() == '\n')
			{
				max_row_count++;
				//Move back
				cur_width = 0;
				column_count = 1;
				//Move to the next row
				cur_height += _tile_height;
			}
			else if (map.peek() == ' ')
			{
				column_count++;
				if (max_column_count < column_count)
				{
					max_column_count = column_count;
				}
				//Move to next tile spot
				cur_width += _tile_width;
			}



			_total_tiles++;
		}

		_level_width = max_column_count *_tile_width;
		_level_height = max_row_count * _tile_height;
		


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
	
	if (!Read_Tiles())
	{
		printf("Failed to load tile set!\n");
		return;
	}
}