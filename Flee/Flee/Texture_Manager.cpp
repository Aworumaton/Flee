#include "Texture_Manager.h"

Texture_Manager::Texture_Manager(SDL_Renderer* renderer)
{
	_sprite_sheet = new Flee_Texture(renderer);

	//Load tile texture
	if (!_sprite_sheet->loadFromFile("Resources/tiles.png"))
	{
		printf("Failed to load tile set texture!\n");
	}

	int tile_height = 80;
	int tile_width = 80;

	_tile_clips = new SDL_Rect[Flee_Sprite_Part::Tile_Type::Count];

	_tile_clips[Flee_Sprite_Part::Tile_Type::TILE_RED].x = 0;
	_tile_clips[Flee_Sprite_Part::Tile_Type::TILE_RED].y = 0;
	_tile_clips[Flee_Sprite_Part::Tile_Type::TILE_RED].w = tile_width;
	_tile_clips[Flee_Sprite_Part::Tile_Type::TILE_RED].h = tile_height;

	_tile_clips[Flee_Sprite_Part::Tile_Type::TILE_GREEN].x = 0;
	_tile_clips[Flee_Sprite_Part::Tile_Type::TILE_GREEN].y = 80;
	_tile_clips[Flee_Sprite_Part::Tile_Type::TILE_GREEN].w = tile_width;
	_tile_clips[Flee_Sprite_Part::Tile_Type::TILE_GREEN].h = tile_height;

	_tile_clips[Flee_Sprite_Part::Tile_Type::TILE_BLUE].x = 0;
	_tile_clips[Flee_Sprite_Part::Tile_Type::TILE_BLUE].y = 160;
	_tile_clips[Flee_Sprite_Part::Tile_Type::TILE_BLUE].w = tile_width;
	_tile_clips[Flee_Sprite_Part::Tile_Type::TILE_BLUE].h = tile_height;

	_tile_clips[Flee_Sprite_Part::Tile_Type::TILE_TOPLEFT].x = 80;
	_tile_clips[Flee_Sprite_Part::Tile_Type::TILE_TOPLEFT].y = 0;
	_tile_clips[Flee_Sprite_Part::Tile_Type::TILE_TOPLEFT].w = tile_width;
	_tile_clips[Flee_Sprite_Part::Tile_Type::TILE_TOPLEFT].h = tile_height;

	_tile_clips[Flee_Sprite_Part::Tile_Type::TILE_LEFT].x = 80;
	_tile_clips[Flee_Sprite_Part::Tile_Type::TILE_LEFT].y = 80;
	_tile_clips[Flee_Sprite_Part::Tile_Type::TILE_LEFT].w = tile_width;
	_tile_clips[Flee_Sprite_Part::Tile_Type::TILE_LEFT].h = tile_height;

	_tile_clips[Flee_Sprite_Part::Tile_Type::TILE_BOTTOMLEFT].x = 80;
	_tile_clips[Flee_Sprite_Part::Tile_Type::TILE_BOTTOMLEFT].y = 160;
	_tile_clips[Flee_Sprite_Part::Tile_Type::TILE_BOTTOMLEFT].w = tile_width;
	_tile_clips[Flee_Sprite_Part::Tile_Type::TILE_BOTTOMLEFT].h = tile_height;

	_tile_clips[Flee_Sprite_Part::Tile_Type::TILE_TOP].x = 160;
	_tile_clips[Flee_Sprite_Part::Tile_Type::TILE_TOP].y = 0;
	_tile_clips[Flee_Sprite_Part::Tile_Type::TILE_TOP].w = tile_width;
	_tile_clips[Flee_Sprite_Part::Tile_Type::TILE_TOP].h = tile_height;

	_tile_clips[Flee_Sprite_Part::Tile_Type::TILE_CENTER].x = 160;
	_tile_clips[Flee_Sprite_Part::Tile_Type::TILE_CENTER].y = 80;
	_tile_clips[Flee_Sprite_Part::Tile_Type::TILE_CENTER].w = tile_width;
	_tile_clips[Flee_Sprite_Part::Tile_Type::TILE_CENTER].h = tile_height;

	_tile_clips[Flee_Sprite_Part::Tile_Type::TILE_BOTTOM].x = 160;
	_tile_clips[Flee_Sprite_Part::Tile_Type::TILE_BOTTOM].y = 160;
	_tile_clips[Flee_Sprite_Part::Tile_Type::TILE_BOTTOM].w = tile_width;
	_tile_clips[Flee_Sprite_Part::Tile_Type::TILE_BOTTOM].h = tile_height;

	_tile_clips[Flee_Sprite_Part::Tile_Type::TILE_TOPRIGHT].x = 240;
	_tile_clips[Flee_Sprite_Part::Tile_Type::TILE_TOPRIGHT].y = 0;
	_tile_clips[Flee_Sprite_Part::Tile_Type::TILE_TOPRIGHT].w = tile_width;
	_tile_clips[Flee_Sprite_Part::Tile_Type::TILE_TOPRIGHT].h = tile_height;

	_tile_clips[Flee_Sprite_Part::Tile_Type::TILE_RIGHT].x = 240;
	_tile_clips[Flee_Sprite_Part::Tile_Type::TILE_RIGHT].y = 80;
	_tile_clips[Flee_Sprite_Part::Tile_Type::TILE_RIGHT].w = tile_width;
	_tile_clips[Flee_Sprite_Part::Tile_Type::TILE_RIGHT].h = tile_height;

	_tile_clips[Flee_Sprite_Part::Tile_Type::TILE_BOTTOMRIGHT].x = 240;
	_tile_clips[Flee_Sprite_Part::Tile_Type::TILE_BOTTOMRIGHT].y = 160;
	_tile_clips[Flee_Sprite_Part::Tile_Type::TILE_BOTTOMRIGHT].w = tile_width;
	_tile_clips[Flee_Sprite_Part::Tile_Type::TILE_BOTTOMRIGHT].h = tile_height;

	Read();
}

Texture_Manager::~Texture_Manager()
{
	delete(_sprite_sheet);
}

Flee_Sprite_Part * Texture_Manager::Create_Sprite_At(int x, int y, int tileType)
{
	return new Flee_Sprite_Part(_sprite_sheet, SDL_Rect{ x, y, _tile_clips[tileType].w, _tile_clips[tileType].h }, tileType, &_tile_clips[tileType]);
}

void Texture_Manager::Read()
{
}

