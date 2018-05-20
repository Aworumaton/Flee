#include "Map_Manager.h"
bool Map_Manager::Read_Tiles()
{
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
		int tiles_capacity = 2500;
		_tileSet = new Flee_Sprite_Part*[tiles_capacity];
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
				tiles_capacity = (int)(max_column_count * max_row_count * 1.8f);
				Flee_Sprite_Part** new_tile_set = new Flee_Sprite_Part*[tiles_capacity];
				for (int i = 0; i < _total_tiles; i++)
				{
					new_tile_set[i] = _tileSet[i];
				}
				delete(_tileSet);
				_tileSet = new_tile_set;
			}

			Flee_Sprite_Part* target = _texture_Manager->Create_Sprite_At(cur_width, cur_height, tileType);
			if (target == nullptr)
			{
				//Stop loading map
				printf("Error loading map: Invalid tile type at %d!\n", _total_tiles);
				tilesLoaded = false;
				break;
			}

			_tileSet[_total_tiles] = target;

			
			if (map.peek() == '\n') //Move to the next row
			{
				max_row_count++;

				cur_width = 0;
				column_count = 1;
				cur_height += _tileSet[_total_tiles]->getBox().h;

			}
			else if (map.peek() == ' ') //Move to next tile spot
			{
				column_count++;
				if (max_column_count < column_count)
				{
					max_column_count = column_count;
				}				
				cur_width += _tileSet[_total_tiles]->getBox().w;
			}
			_total_tiles++;
		}

		_level_width = cur_width + _tileSet[_total_tiles-1]->getBox().w;
		_level_height = cur_height + _tileSet[_total_tiles-1]->getBox().h;


		//Close the file
		map.close();
	}


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
		if (_tileSet[i]->Is_Wall())
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
	//Deallocate tiles
	for (int i = 0; i < _total_tiles; ++i)
	{
		if (_tileSet[i] != NULL)
		{
			delete _tileSet[i];
			_tileSet[i] = NULL;
		}
	}
	delete(_tileSet);
	_renderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
}

Map_Manager::Map_Manager(SDL_Renderer* renderer, Texture_Manager* texture_Manager)
{
	_renderer = renderer;
	_texture_Manager = texture_Manager;


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