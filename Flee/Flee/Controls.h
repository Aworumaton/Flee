/*
*	Author: Omer Sari
*/
#ifndef CONTROLS_H
#define CONTROLS_H

class Main_Agent_Controls
{
public:
	int look_at_x;
	int look_at_y;
	bool move_forward;
	bool move_backward;
	bool move_left;
	bool move_right;

	bool sprint;

	bool on_action;
	bool active_action;

	void reset()
	{
		move_forward = false;
		move_backward = false;
		move_left = false;
		move_right = false;
		sprint = false;
		on_action = false;
		active_action = false;
	}
};

class Game_Controls
{
public:
	bool escape;
	bool pause;

	void reset()
	{
		escape = false;
		pause = false;
	}
};

#endif