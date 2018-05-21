#include "Texture_Manager.h"

Texture_Manager* Texture_Manager::_current;

Texture_Manager::Texture_Manager(){}

Texture_Manager::~Texture_Manager()
{
	_current = NULL;
	delete(_sprite_sheet);
}

bool Texture_Manager::Initialize(SDL_Renderer* renderer)
{
	if (_current != nullptr)
	{
		delete(_current);
	}

	_current = new Texture_Manager();

	_current->_sprite_sheet = new Flee_Texture(renderer);

	//Load tile texture
	if (!_current->_sprite_sheet->loadFromFile("Resources/sprite_sheet.png"))
	{
		printf("Failed to load tile set texture!\n");
		return false;
	}

	bool success = _current->Read_Sprites();
	if (success)
	{
		success = _current->Read_Animations();
	}
	return success;
}

void Texture_Manager::Free()
{
	delete(_current);
}

Flee_Sprite_Part * Texture_Manager::Create_Sprite(std::string sprite_id)
{
	Flee_Sprite* target = _current->Get_Flee_Sprite(sprite_id);
	if (target == nullptr)
	{
		return nullptr;
	}
	return new Flee_Sprite_Part(_current->_sprite_sheet, target->flags, &(target->bounds));
}

Flee_Animated_Sprite_Part * Texture_Manager::Create_Animated_Sprite(std::string id)
{
	int count = _current->_animated_sprite_count;
	Flee_Animated_Sprite*  clips = _current->_animations;

	for (int i = 0; i < count; i++)
	{
		Flee_Animated_Sprite* target = &clips[i];
		if (id.compare(target->string_id) == 0)
		{
			SDL_Rect** return_sprites = new SDL_Rect*[target->animation_frame_count];

			for (int j = 0; j < target->animation_frame_count; j++)
			{
				return_sprites[j] = &(target->animation_targets[j]->bounds);
			}

			return new Flee_Animated_Sprite_Part(_current->_sprite_sheet, target->animation_frame_count, return_sprites);
		}
	}

	return nullptr;
}

bool Texture_Manager::Read_Animations()
{
	//Success flag
	bool success = true;

	std::ifstream file("Resources/animations.txt");

	if (!file.is_open())
	{
		printf("Unable to load sprite animations file!\n");
		success = false;
	}
	else
	{
		int capacity = 32;
		_animations = new Flee_Animated_Sprite[capacity];
		_animated_sprite_count = 0;
		std::string string_id = "";
		while (file >> string_id)
		{
			Flee_Animated_Sprite target;
			target.string_id = string_id;
			if (file.eof())
			{
				printf("Unable to parse sprite sheet file!\n");
				success = false;
				break;
			}
			
			file >> target.animation_frame_count;
			if (file.eof())
			{
				printf("Unable to parse sprite sheet file!\n");
				success = false;
				break;
			}

			target.animation_targets = new Flee_Sprite*[target.animation_frame_count];
			for (int i = 0; i < target.animation_frame_count; i++)
			{
				std::string sprite_id;
				if (file.eof())
				{
					printf("Unable to parse sprite sheet file!\n");
					success = false;
					break;
				}
				file >> sprite_id;

				target.animation_targets[i] = Get_Flee_Sprite(sprite_id);
			}

			if (capacity == _animated_sprite_count)
			{
				capacity = (int)(capacity * 1.8f);
				Flee_Animated_Sprite* new_set = new Flee_Animated_Sprite[capacity];
				for (int i = 0; i < _animated_sprite_count; i++)
				{
					new_set[i] = _animations[i];
				}
			//	delete(_tile_clips);
				_animations = new_set;
			}

			_animations[_animated_sprite_count] = target;
			_animated_sprite_count++;
		}

		//Close the file
		file.close();
	}

	//If the map was loaded fine
	return success;
}




bool Texture_Manager::Read_Sprites()
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
		std::string string_id = "";
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

Texture_Manager::Flee_Sprite* Texture_Manager::Get_Flee_Sprite(std::string string_id)
{
	int count = _current->_sprite_count;
	Flee_Sprite*  tile_clips = _current->_tile_clips;

	for (int i = 0; i < count; i++)
	{
		Flee_Sprite* target = &tile_clips[i];
		if (string_id.compare(target->string_id) == 0)
		{
			return target;
		}
	}

	return nullptr;
}