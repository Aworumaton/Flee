#ifndef CONTROLS_H
#define CONTROLS_H

class Main_Agent_Controls
{
public:
	bool move_forward;
	bool move_backward;
	bool move_left;
	bool move_right;

	bool action;

	void reset()
	{
		move_forward = false;
		move_backward = false;
		move_left = false;
		move_right = false;
		action = false;
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