#pragma once

#include <memory>
#include <deque>

#include "raylib-cpp.hpp"
#include "Globals.h"

class Food
{
public:
	Food();
	void Draw();
	void changePosition(std::deque<RVector2> snakeBody);
	RVector2 getPosition();

private:
	RVector2 position;
	RVector2 randomPos();
	std::unique_ptr<RTexture> texture;
};