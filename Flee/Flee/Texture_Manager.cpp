#include "Texture_Manager.h"

Texture_Manager::Texture_Manager(SDL_Renderer* renderer)
{
	_sprite_sheet = new Flee_Texture(renderer);

	//Load tile texture
	if (!_sprite_sheet->loadFromFile("Resources/sprite_sheet.png"))
	{
		printf("Failed to load tile set texture!\n");
	}

	Read();
}

Texture_Manager::~Texture_Manager()
{
	delete(_sprite_sheet);
}

Flee_Sprite_Part * Texture_Manager::Create_Sprite(string sprite_id)
{
	for (int i = 0; i < _sprite_count; i++)
	{
		Flee_Sprite* target = &_tile_clips[i];
		if (sprite_id.compare(target->string_id) == 0)
		{
			return new Flee_Sprite_Part(_sprite_sheet, target->flags, &(target->bounds));
		}
	}

	return nullptr;
}

int Texture_Manager::Get_Sprite_Count()
{
	return _sprite_count;
}

bool Texture_Manager::Read()
{
	//Success flag
	bool success = true;

	//Open the map
	std::ifstream file("Resources/sprite_sheet.txt");

	//If the map couldn't be loaded
	if (!file.is_open())
	{
		printf("Unable to load sprite sheet file!\n");
		success = false;
	}
	else
	{
		int capacity = 32;
		_tile_clips = new Flee_Sprite[capacity];
		_sprite_count = 0;
		string string_id = "";
		while (file >> string_id)
		{
			Flee_Sprite target;
			target.string_id = string_id;
			if (file.eof())
			{
				printf("Unable to parse sprite sheet file!\n");
				success = false;
				break;
			}
			//
			//file >> target.id;
			//if (file.eof())
			//{
			//	printf("Unable to parse sprite sheet file!\n");
			//	success = false;
			//	break;
			//}
			
			file >> target.flags;
			if (file.eof())
			{
				printf("Unable to parse sprite sheet file!\n");
				success = false;
				break;
			}

			file >> target.bounds.x;
			if (file.eof())
			{
				printf("Unable to parse sprite sheet file!\n");
				success = false;
				break;
			}

			file >> target.bounds.y;
			if (file.eof())
			{
				printf("Unable to parse sprite sheet file!\n");
				success = false;
				break;
			}

			file >> target.bounds.w;
			if (file.eof())
			{
				printf("Unable to parse sprite sheet file!\n");
				success = false;
				break;
			}
			
			file >> target.bounds.h;

			if (capacity == _sprite_count)
			{
				capacity = (int)(capacity * 1.8f);
				Flee_Sprite* new_tile_set = new Flee_Sprite[capacity];
				for (int i = 0; i < _sprite_count; i++)
				{
					new_tile_set[i] = _tile_clips[i];
				}
			//	delete(_tile_clips);
				_tile_clips = new_tile_set;
			}

			_tile_clips[_sprite_count] = target;
			_sprite_count++;
		}

		//Close the file
		file.close();
	}

	//If the map was loaded fine
	return success;
}

