/*
*	Author: Omer Sari
*/
#include "FleeRenderer.h"

const int FleeRenderer::SCREEN_WIDTH = 800;
const int FleeRenderer::SCREEN_HEIGHT = 600;

FleeRenderer* FleeRenderer::_current;

FleeRenderer::FleeRenderer(bool& success)
{
	success = false;



	//Create window
	_window = SDL_CreateWindow("Flee", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, FleeRenderer::SCREEN_WIDTH, FleeRenderer::SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (_window == NULL)
	{
		printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
		return;
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

	_camera = new FleeTransform();
	_camera->X = 0;
	_camera->Y = 0;
	_camera->Width = FleeRenderer::SCREEN_WIDTH;
	_camera->Height = FleeRenderer::SCREEN_HEIGHT;
	
	_spriteSheet = new FleeTexture(_renderer);

	//Load tile texture
	if (!_spriteSheet->LoadFromFile("Resources/sprite_sheet.png"))
	{
		printf("Failed to load tile set texture!\n");
		return;
	}

	ReadSprites();

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

bool FleeRenderer::Register(SpriteData* spriteData, Constants::VisualLayers layerIndex)
{
	return  _current->RegisterSprite(spriteData, layerIndex);
}


bool FleeRenderer::RegisterSprite(SpriteData* spriteData, Constants::VisualLayers layerIndex)
{
	int targetSize = (int)layerIndex + 1;
	while (Layers.Size() < targetSize)
	{
		Layers.Add(new FleeList<SpriteDataSpritePair*>());
	}

	SpriteDataSpritePair* pair = new SpriteDataSpritePair();
	pair->SpriteData = spriteData;
	pair->Sprite = GetSprite(spriteData->Id());
	if (pair->Sprite == nullptr)
	{
		return false;
	}
	
	if (!spriteData->InitializeWith(pair->Sprite->Flags, pair->Sprite->Transform.Width, pair->Sprite->Transform.Height))
	{
		return false;
	}


	Layers.ItemAt(layerIndex)->Add(pair);
	return true;
}

void FleeRenderer::Tick(int dt)
{
	_current->RenderTick(dt);
}

FleeTransform* FleeRenderer::GetCamera()
{
	return _current->_camera;
}

void FleeRenderer::RenderTick(int dt)
{
	//Clear screen
	SDL_SetRenderDrawColor(_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(_renderer);


	FleeTransform* wordlTransform = new FleeTransform();

	for (int layerIndex = 0; layerIndex < Layers.Size(); layerIndex++)
	{
		FleeList<SpriteDataSpritePair*>* SpriteDataSpriteList = Layers.ItemAt(layerIndex);
		for (int i = 0; i < SpriteDataSpriteList->Size(); i++)
		{
			SpriteDataSpritePair* pair = SpriteDataSpriteList->ItemAt(i);
			if (!pair->SpriteData->IsHidden)
			{
				wordlTransform->X = pair->SpriteData->Transform->X - _camera->X;
				wordlTransform->Y = pair->SpriteData->Transform->Y - _camera->Y;
				wordlTransform->Width = pair->SpriteData->Transform->Width;
				wordlTransform->Height = pair->SpriteData->Transform->Height;
				wordlTransform->Rotation = pair->SpriteData->Transform->Rotation;

				if (Constants::CheckCollision(pair->SpriteData->Transform, _camera))
				{
					_spriteSheet->Render(&pair->Sprite->Transform, wordlTransform);
				}
			}
		}
	}

	delete(wordlTransform);


	//Update screen
	SDL_RenderPresent(_renderer);
}

bool FleeRenderer::ReadSprites()
{

	//Open the map
	std::ifstream file("Resources/sprite_sheet.txt");

	//If the map couldn't be loaded
	if (!file.is_open())
	{
		printf("Unable to load sprite sheet file!\n");
		return false;
	}


	std::string string_id = "";
	while (file >> string_id)
	{
		Sprite* target = new Sprite();
		target->Id = string_id;
		file >> target->Transform.X;
		file >> target->Transform.Y;
		file >> target->Transform.Width;
		file >> target->Transform.Height;
			
		_sprites.Add(target);
	}

	//Close the file
	file.close();
	return true;
}

FleeRenderer::Sprite* FleeRenderer::GetSprite(std::string id)
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