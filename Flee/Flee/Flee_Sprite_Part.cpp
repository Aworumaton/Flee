#include "Flee_Sprite_Part.h"

Flee_Sprite_Part::Flee_Sprite_Part(Flee_Texture * sheet, int x, int y, unsigned flags, SDL_Rect * rect)
{
	_sprite_sheet_rect = rect;
	_render_rect = SDL_Rect{ x, y, rect->w, rect->h };
	_sprite_sheet = sheet;

	_flags = flags;
}

void Flee_Sprite_Part::render(SDL_Rect& camera)
{
	//If the tile is on screen
	if (Constants::checkCollision(camera, _render_rect))
	{
		//Show the tile
		_sprite_sheet->render(_render_rect.x - camera.x, _render_rect.y - camera.y, _sprite_sheet_rect);
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
