#pragma once

#include <deque>

#include "raylib-cpp.hpp"
#include "Globals.h"

class Snake
{
public:
	char getLastMovement();
	void setDirection(RVector2 newDirection);
	RVector2 getHeadPos();
	std::deque<RVector2> getBody();
	void Grow();
	void Reset();
	void Draw();
	void Update();

private:
	std::deque<RVector2> body = { {4,6}, {3,6}, {2,6} };
	RVector2 direction = { 1,0 };
	char lastMovement = 'r';
	bool addSegment = false;
};