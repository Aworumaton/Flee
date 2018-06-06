#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include <stdio.h>
#include <chrono>
#include "Controls.h"
#include "Input.h"
#include "Constants.h"
#include "Scene.h"
#include "Player.h"
#include "Enemy.h"
#include "AnimationManager.h"
//#include "Texture_Manager.h"

class Game
{
public:
	static Game* CreateGame();

	void Run();

	~Game();
private:
	Input _input;
	Scene* _scene;

	//The dot that will be moving around on the screen
	Player* _player;
	Enemy* _enemy;

	bool _isRunning;
	Game();


	bool Initialize();

	void Tick(int dt);

	void GameTick(int dt);
	void Exit();
};

#endif