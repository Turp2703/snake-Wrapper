#include "Snake.h"

char Snake::getLastMovement()
{
	return lastMovement;
}

void Snake::setDirection(RVector2 newDirection)
{
	direction = newDirection;
}

RVector2 Snake::getHeadPos()
{
	return body.front();
}

std::deque<RVector2> Snake::getBody()
{
	return body;
}

void Snake::Grow()
{
	addSegment = true;
}

void Snake::Reset()
{
	body = { {4,6}, {3,6}, {2,6} };
	direction = { 1,0 };
	lastMovement = 'r';
}

void Snake::Draw()
{
	for (auto& segment : body) {
		RRectangle rect(segment.x * kCellSize + kOffset, segment.y * kCellSize + kOffset, (float)kCellSize, (float)kCellSize);
		DrawRectangleRounded(rect, 0.5, 6, kColorDarkGreen);
	}
}

void Snake::Update()
{
	body.push_front(body.front() + direction);
	
	if (addSegment) {
		addSegment = false;
	}
	else {
		body.pop_back();
	}
	
	if (direction.x == 1) { lastMovement = 'r'; }
	else if (direction.x == -1) { lastMovement = 'l'; }
	else if (direction.y == 1) { lastMovement = 'd'; }
	else { lastMovement = 'u'; }
}
