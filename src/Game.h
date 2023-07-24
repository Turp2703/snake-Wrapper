#pragma once

#include "raylib-cpp.hpp"

#include "Globals.h"
#include "Snake.h"
#include "Food.h"

class Game
{
public:
	void Run();

private:	
	RWindow window;

	void Initialize();
	void Shutdown();

	double lastUpdateTime;
	bool shouldUpdate(double interval);

	bool running;
	void HandleEvents();
	void Update();
	void Draw();
	void GameOver();

	int score;
	Snake snake;
	Food *food;

	RSound scoreSound;
	RSound gameOverSound;
};