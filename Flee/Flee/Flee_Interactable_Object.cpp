#include "Flee_Interactable_Object.h"

Flee_Interactable_Object::Flee_Interactable_Object(Flee_Animated_Sprite_Part * visual)
{
	_visual = visual;
}

bool Flee_Interactable_Object::Is_Door()
{
	return (_visual->Get_Flags() & Flee_Sprite_Part_Base::Sprite_Flags::Door) == Flee_Sprite_Part_Base::Sprite_Flags::Door;
}

bool Flee_Interactable_Object::Is_Obstruction()
{
	if (Is_Door())
	{
		int current_state = _visual->Get_Frame_Index();
		return current_state == 0;
	}
	return true;
}

bool Flee_Interactable_Object::Is_Hiding_Place()
{
	return (_visual->Get_Flags() & Flee_Sprite_Part_Base::Sprite_Flags::Hiding_Place) == Flee_Sprite_Part_Base::Sprite_Flags::Hiding_Place;
}

void Flee_Interactable_Object::Tick(int dt)
{
}

void Flee_Interactable_Object::OnAction()
{
	printf("ON ACTION\n");
	if (Is_Door())
	{
		int current_state = _visual->Get_Frame_Index();
		_visual->Set_Frame_Index((current_state + 1) % 2);
	}
	else if (Is_Hiding_Place())
	{
	//	int current_state = _visual->Get_Frame_Index();
	//	_visual->Set_Frame_Index((current_state + 1) % 2);
	}
}

void Flee_Interactable_Object::Render(SDL_Rect & camera, double angle, SDL_Point * center, SDL_RendererFlip flip)
{
	_visual->Render(camera, angle, center, flip);
}

void Flee_Interactable_Object::Set_Position(int x, int y)
{
	_visual->Set_Position(x, y);
}

SDL_Rect Flee_Interactable_Object::getBox()
{
	return _visual->getBox();
}
