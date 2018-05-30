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






			SpriteData* sData = new SpriteData();

			sData->Transform.Y = cur_height;
			sData->Transform.X = cur_width;
			sData->Transform.Height = -1;
			sData->Transform.Width = -1;

			sData->Id = "Tile_" + std::to_string(tileType);
			
			if (!FleeRenderer::Register(sData))
			{
				//Stop loading map
				printf("Error loading map: Invalid tile type at %d!\n", _total_tiles);
				loaded = false;
				break;
			}

			_layout.Add(sData);


			if (map.peek() == '\n') //Move to the next row
			{
				max_row_count++;

				cur_width = 0;
				column_count = 1;
				cur_height += sData->Transform.Height;

			}
			else if (map.peek() == ' ') //Move to next tile spot
			{
				column_count++;
				if (max_column_count < column_count)
				{
					max_column_count = column_count;
				}
				cur_width += sData->Transform.Width;
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
			_level_width = cur_width + _layout.ItemAt(_layout.Size() - 1)->Transform.Width;
			_level_height = cur_height + _layout.ItemAt(_layout.Size() - 1)->Transform.Height;
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
		int capacity = 32;
		_objects = new Flee_Interactable_Object*[capacity];
		_total_objects = 0;
		std::string string_id = "";
		while (file >> string_id)
		{
			unsigned int flags;
			int x;
			int y;

			file >> flags;
			file >> x;
			file >> y;


			if (capacity == _total_objects)
			{
				capacity = (int)(capacity * 1.8f);
				Flee_Interactable_Object** new_set = new Flee_Interactable_Object*[capacity];
				for (int i = 0; i < _total_objects; i++)
				{
					new_set[i] = _objects[i];
				}
				//	delete(_tile_clips);
				_objects = new_set;
			}

			//Flee_Animated_Sprite_Part* target_Sprite = Texture_Manager::Create_Animated_Sprite(string_id);
			//Flee_Interactable_Object* target = new Flee_Interactable_Object(target_Sprite);

			//target->Set_Position(x, y);
			//_objects[_total_objects] = target;
			//_total_objects++;
		}

		//Close the file
		file.close();
	}


	//If the map was loaded fine
	return loaded;
}

int Map_Manager::Get_Level_Width()
{
	return _level_width;
}
int Map_Manager::Get_Level_Height()
{
	return _level_height;
}

Flee_Interactable_Object* Map_Manager::Get_First_Objet_Under(SDL_Point point)
{
	for (int i = 0; i < _total_objects; i++)
	{
		Flee_Interactable_Object* target = _objects[i];
		if (Constants::checkCollision(target->getBox(), point))
		{
			return target;
		}
	}

	return nullptr;
}

bool Map_Manager::touches_walls(SDL_Rect box)
{
	//Go through the tiles
	//for (int i = 0; i < _total_tiles; ++i)
	//{
	//	//If the tile is a wall type tile
	//	if (_tileSet[i]->Is_Wall())
	//	{
	//		//If the collision box touches the wall tile
	//		if (Constants::checkCollision(box, _tileSet[i]->getBox()))
	//		{
	//			return true;
	//		}
	//	}
	//}
	//
	//
	//for (int i = 0; i < _total_objects; ++i)
	//{
	//	if (_objects[i]->Is_Obstruction())
	//	{
	//		if (Constants::checkCollision(box, _objects[i]->getBox()))
	//		{
	//			return true;
	//		}
	//	}
	//}

	//If no wall tiles were touched
	return false;
}

void Map_Manager::Tick(int dt)
{
	for (int i = 0; i < _total_objects; ++i)
	{
		_objects[i]->Tick(dt);
	}
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

}

Map_Manager::Map_Manager()
{	
	if (!Read())
	{
		printf("Failed to load tile set!\n");
		return;
	}
}