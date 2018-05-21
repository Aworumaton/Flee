#include "Map_Manager.h"
bool Map_Manager::Read()
{
	//Success flag
	bool loaded = true;

	//Open the map
	std::ifstream map("Resources/level_0.txt");

	//If the map couldn't be loaded
	if (!map.is_open())
	{
		printf("Unable to load map file!\n");
		loaded = false;
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

			Flee_Sprite_Part* target = Texture_Manager::Create_Sprite("Tile_" + std::to_string(tileType));
			target->Set_Position(cur_width, cur_height);
			if (target == nullptr)
			{
				//Stop loading map
				printf("Error loading map: Invalid tile type at %d!\n", _total_tiles);
				loaded = false;
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
		if (_total_tiles == 0)
		{
			printf("No tiles were loaded %d!\n", _total_tiles);
			loaded = false;
		}
		else
		{
			_level_width = cur_width + _tileSet[_total_tiles - 1]->getBox().w;
			_level_height = cur_height + _tileSet[_total_tiles - 1]->getBox().h;
		}
		//Close the file
		map.close();
	}



	//Open the map
	std::ifstream file("Resources/level_0_objects.txt");

	//If the map couldn't be loaded
	if (!file.is_open())
	{
		printf("Unable to load map objects file!\n");
		loaded = false;
	}
	else
	{
		//int capacity = 32;
		//_tile_clips = new Flee_Sprite[capacity];
		//_sprite_count = 0;
		//string string_id = "";
		//while (file >> string_id)
		//{
		//	Flee_Sprite target;
		//	target.string_id = string_id;
		//	if (file.eof())
		//	{
		//		printf("Unable to parse sprite sheet file!\n");
		//		loaded = false;
		//		break;
		//	}
		//
		//	file >> target.id;
		//	if (file.eof())
		//	{
		//		printf("Unable to parse sprite sheet file!\n");
		//		loaded = false;
		//		break;
		//	}
		//
		//	file >> target.flags;
		//	if (file.eof())
		//	{
		//		printf("Unable to parse sprite sheet file!\n");
		//		loaded = false;
		//		break;
		//	}
		//
		//	file >> target.bounds.x;
		//	if (file.eof())
		//	{
		//		printf("Unable to parse sprite sheet file!\n");
		//		loaded = false;
		//		break;
		//	}
		//
		//	file >> target.bounds.y;
		//	if (file.eof())
		//	{
		//		printf("Unable to parse sprite sheet file!\n");
		//		loaded = false;
		//		break;
		//	}
		//
		//	file >> target.bounds.w;
		//	if (file.eof())
		//	{
		//		printf("Unable to parse sprite sheet file!\n");
		//		loaded = false;
		//		break;
		//	}
		//
		//	file >> target.bounds.h;
		//
		//	if (capacity == _sprite_count)
		//	{
		//		capacity = (int)(capacity * 1.8f);
		//		Flee_Sprite* new_tile_set = new Flee_Sprite[capacity];
		//		for (int i = 0; i < _sprite_count; i++)
		//		{
		//			new_tile_set[i] = _tile_clips[i];
		//		}
		//		//	delete(_tile_clips);
		//		_tile_clips = new_tile_set;
		//	}
		//
		//	_tile_clips[_sprite_count] = target;
		//	_sprite_count++;
		//}

		//Close the file
		file.close();
	}


	//If the map was loaded fine
	return loaded;
}


void Map_Manager::Render(SDL_Rect &camera)
{
	//Render level
	for (int i = 0; i < _total_tiles; ++i)
	{
		_tileSet[i]->Render(camera);
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

Map_Manager::Map_Manager(SDL_Renderer* renderer)
{
	_renderer = renderer;

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
	
	if (!Read())
	{
		printf("Failed to load tile set!\n");
		return;
	}
}