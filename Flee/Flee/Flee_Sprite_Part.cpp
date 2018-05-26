#include "Flee_Sprite_Part.h"

Flee_Sprite_Part::Flee_Sprite_Part(Flee_Texture * sheet, unsigned flags, SDL_Rect * sprite_rect)
{
	_sprite_sheet_rect = sprite_rect;
	_render_rect = SDL_Rect{ 0,0,sprite_rect->w,sprite_rect->h };
	_sprite_sheet = sheet;

	_flags = flags;
}

void Flee_Sprite_Part::Set_Position(int x, int y)
{
	_render_rect.x = x;
	_render_rect.y = y;
}

void Flee_Sprite_Part::Render(SDL_Rect& camera, double angle, SDL_Point* center, SDL_RendererFlip flip)
{
	//If the tile is on screen
	if (Constants::checkCollision(camera, _render_rect))
	{
		//Show the tile
		_sprite_sheet->render(_render_rect.x - camera.x, _render_rect.y - camera.y, _sprite_sheet_rect, angle, center, flip);
	}
}

SDL_Rect Flee_Sprite_Part::getBox()
{
	return _render_rect;
}

bool Flee_Sprite_Part::Is_Wall()
{
	return (_flags & Sprite_Flags::Wall) == Sprite_Flags::Wall;
}


unsigned int Flee_Sprite_Part::Get_Flags()
{
	return _flags;
}
