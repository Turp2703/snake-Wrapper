#include "Food.h"

Food::Food()
{
	position = { kCellCount / 2, kCellCount / 2 };
	texture = std::make_unique<RTexture>("assets/food.png");
}

void Food::Draw()
{
	DrawTexture(*texture, (int)position.x * kCellSize + kOffset, (int)position.y * kCellSize + kOffset, WHITE);
	//DrawRectangle((int)position.x * kCellSize, (int)position.y * kCellSize, 5, 5, kColorDarkGreen);
}

void Food::changePosition(std::deque<RVector2> snakeBody)
{
	RVector2 newPos;
	bool insideSnake;
	do {
		insideSnake = false;
		newPos = randomPos();
		for (auto& segment : snakeBody) {
			if (newPos == segment) { insideSnake = true; }
		}
	} while (insideSnake);
	position = newPos;
}

RVector2 Food::getPosition()
{
	return position;
}

RVector2 Food::randomPos()
{
	return RVector2((float)GetRandomValue(0, kCellCount - 1), (float)GetRandomValue(0, kCellCount - 1));
} 