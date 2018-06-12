/*
*	Author: Omer Sari
*/
#ifndef INPUT_H
#define INPUT_H

#include <SDL.h>
#include <stdio.h>
#include "Controls.h"

class Input
{
public:
	Input();
	~Input();
	Game_Controls _game_controls;
	Main_Agent_Controls _main_agent_controls;
	bool force_exit;
	void Tick(int dt);
};

#endif