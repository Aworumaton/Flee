#include "FleeRenderer.h"

const int FleeRenderer::SCREEN_WIDTH = 800;
const int FleeRenderer:: SCREEN_HEIGHT = 600;

FleeRenderer* FleeRenderer::_current;

FleeRenderer::FleeRenderer(bool& success)
{
	success = false;



	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		return;
	}
	else
	{
		//Create window
		_window = SDL_CreateWindow("Flee", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, FleeRenderer::SCREEN_WIDTH, FleeRenderer::SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (_window == NULL)
		{
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			return;
		}
	}

	//Create renderer for window
	_renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	//Initialize renderer color
	SDL_SetRenderDrawColor(_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	_screen_surface = SDL_GetWindowSurface(_window);

	//Initialize PNG loading
	int imgFlags = IMG_INIT_PNG;

	if (!(IMG_Init(imgFlags) & imgFlags))
	{
		printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
		return;
	}



	_camera = new Transform();
	_camera->X = 0;
	_camera->Y = 0;
	_camera->Width = FleeRenderer::SCREEN_WIDTH;
	_camera->Height = FleeRenderer::SCREEN_HEIGHT;
	
	_spriteSheet = new Flee_Texture(_renderer);

	//Load tile texture
	if (!_spriteSheet->loadFromFile("Resources/sprite_sheet.png"))
	{
		printf("Failed to load tile set texture!\n");
		return;
	}

	FleeList<Sprite*>* sprites = ReadSprites();
	if (sprites == nullptr)
	{
		//	success = _current->Read_Animations();
		return;
	}
	_sprites = *sprites;


	success = true;
}

FleeRenderer::~FleeRenderer()
{
	delete(_spriteSheet);
	delete(&_sprites);

	if (_renderer != NULL)
	{
		//Destroy renderer
		SDL_DestroyRenderer(_renderer);
		_renderer = NULL;
	}
	if (_window != NULL)
	{
		//Destroy window
		SDL_DestroyWindow(_window);
		_window = NULL;
	}

	//Quit SDL subsystems
	IMG_Quit();
}

bool FleeRenderer::Initialize()
{
	
	if (_current != nullptr)
	{
		_current->Free();
	}
	bool success;
	_current = new FleeRenderer(success);
	return success;
}

void FleeRenderer::Free()
{
	delete(_current);
}

bool FleeRenderer::Register(SpriteData* spriteData)
{
	return  _current->RegisterSprite(spriteData);
}


bool FleeRenderer::RegisterSprite(SpriteData* spriteData)
{
	SpriteDataSpritePair* pair = new SpriteDataSpritePair();
	pair->SpriteData = spriteData;
	pair->Sprite = GetSprite(spriteData->Id);
	if (pair->Sprite == nullptr)
	{
		return false;
	}


	if (spriteData->Transform.Width < 0)
	{
		spriteData->Transform.Width = pair->Sprite->Transform.Width;
	}

	if (spriteData->Transform.Height < 0)
	{
		spriteData->Transform.Height = pair->Sprite->Transform.Height;
	}


	SpriteDataSpriteList.Add(pair);
	return true;
}

void FleeRenderer::Tick(float dt)
{
	_current->RenderTick(dt);
}

Transform* FleeRenderer::GetCamera()
{
	return _current->_camera;
}

void FleeRenderer::RenderTick(float dt)
{
	//Clear screen
	SDL_SetRenderDrawColor(_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(_renderer);


	Transform* wordlTransform = new Transform();

	for (int i = 0; i < SpriteDataSpriteList.Size(); i++)
	{
		SpriteDataSpritePair* pair = SpriteDataSpriteList.ItemAt(i);
		if (!pair->SpriteData->IsHidden)
		{
			wordlTransform->X = pair->SpriteData->Transform.X - _camera->X;
			wordlTransform->Y = pair->SpriteData->Transform.Y - _camera->Y;
			wordlTransform->Width = pair->SpriteData->Transform.Width;
			wordlTransform->Height = pair->SpriteData->Transform.Height;
			wordlTransform->Rotation = pair->SpriteData->Transform.Rotation;

			_spriteSheet->Render(&pair->Sprite->Transform, wordlTransform);
		}
	}

	delete(wordlTransform);


	//Update screen
	SDL_RenderPresent(_renderer);
}
//Flee_Animated_Sprite_Part * FleeRenderer::Create_Animated_Sprite(std::string id)
//{
//	int count = _current->_animated_sprite_count;
//	Flee_Animated_Sprite*  clips = _current->_animations;
//
//	for (int i = 0; i < count; i++)
//	{
//		Flee_Animated_Sprite* target = &clips[i];
//		if (id.compare(target->string_id) == 0)
//		{
//			SDL_Rect** return_sprites = new SDL_Rect*[target->animation_frame_count];
//			unsigned int* return_flags =new unsigned int[target->animation_frame_count];
//
//			for (int j = 0; j < target->animation_frame_count; j++)
//			{
//				return_sprites[j] = &(target->animation_targets[j]->bounds);
//				return_flags[j] = target->animation_targets[j]->flags;
//			}
//
//			return new Flee_Animated_Sprite_Part(_current->_sprite_sheet, target->animation_frame_count, return_sprites, return_flags);
//		}
//	}
//
//	return nullptr;
//}

//bool FleeRenderer::Read_Animations()
//{
//	//Success flag
//	bool success = true;
//
//	std::ifstream file("Resources/animations.txt");
//
//	if (!file.is_open())
//	{
//		printf("Unable to load sprite animations file!\n");
//		success = false;
//	}
//	else
//	{
//		int capacity = 32;
//		_animations = new Flee_Animated_Sprite[capacity];
//		_animated_sprite_count = 0;
//		std::string string_id = "";
//		while (file >> string_id)
//		{
//			Flee_Animated_Sprite target;
//			target.string_id = string_id;
//			if (file.eof())
//			{
//				printf("Unable to parse sprite sheet file!\n");
//				success = false;
//				break;
//			}
//			
//			file >> target.animation_frame_count;
//			if (file.eof())
//			{
//				printf("Unable to parse sprite sheet file!\n");
//				success = false;
//				break;
//			}
//
//			target.animation_targets = new Flee_Sprite*[target.animation_frame_count];
//			for (int i = 0; i < target.animation_frame_count; i++)
//			{
//				std::string sprite_id;
//				if (file.eof())
//				{
//					printf("Unable to parse sprite sheet file!\n");
//					success = false;
//					break;
//				}
//				file >> sprite_id;
//
//				target.animation_targets[i] = Get_Flee_Sprite(sprite_id);
//			}
//
//			if (capacity == _animated_sprite_count)
//			{
//				capacity = (int)(capacity * 1.8f);
//				Flee_Animated_Sprite* new_set = new Flee_Animated_Sprite[capacity];
//				for (int i = 0; i < _animated_sprite_count; i++)
//				{
//					new_set[i] = _animations[i];
//				}
//			//	delete(_tile_clips);
//				_animations = new_set;
//			}
//
//			_animations[_animated_sprite_count] = target;
//			_animated_sprite_count++;
//		}
//
//		//Close the file
//		file.close();
//	}
//
//	//If the map was loaded fine
//	return success;
//}




FleeList<Sprite*>* FleeRenderer::ReadSprites()
{

	//Open the map
	std::ifstream file("Resources/sprite_sheet.txt");

	//If the map couldn't be loaded
	if (!file.is_open())
	{
		printf("Unable to load sprite sheet file!\n");
		return nullptr;
	}

	FleeList<Sprite*>* sprites = new FleeList<Sprite*>();

	std::string string_id = "";
	while (file >> string_id)
	{
		Sprite* target = new Sprite();
		target->Id = string_id;
		if (file.eof())
		{
			printf("Unable to parse sprite sheet file!\n");
			delete(sprites);
			return nullptr;
		}
		file >> target->Flags;


		if (file.eof())
		{
			printf("Unable to parse sprite sheet file!\n");
			delete(sprites);
			return nullptr;
		}
		file >> target->Transform.X;


		if (file.eof())
		{
			printf("Unable to parse sprite sheet file!\n");
			delete(sprites);
			return nullptr;
		}
		file >> target->Transform.Y;


		if (file.eof())
		{
			printf("Unable to parse sprite sheet file!\n");
			delete(sprites);
			return nullptr;
		}
		file >> target->Transform.Width;


		if (file.eof())
		{
			printf("Unable to parse sprite sheet file!\n");
			delete(sprites);
			return nullptr;
		}
		file >> target->Transform.Height;
			
		sprites->Add(target);
	}

	//Close the file
	file.close();

	//If the map was loaded fine
	return sprites;
}

Sprite* FleeRenderer::GetSprite(std::string id)
{
	for (int i = 0; i < _sprites.Size(); i++)
	{
		if (_sprites.ItemAt(i)->Id == id)
		{
			return _sprites.ItemAt(i);
		}
	}

	return nullptr;
}