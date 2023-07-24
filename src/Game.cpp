#include "Game.h"

void Game::Run()
{
	Initialize();
	while (!window.ShouldClose()) {
		HandleEvents();
		if (running) { Update(); }
		Draw();
	}
}

void Game::Initialize()
{
	// Window
	window = RWindow(kScreenSize + 2 * kOffset, kScreenSize + 2 * kOffset, "Snake-Wrapper");
	SetExitKey(KEY_NULL);
	window.SetTargetFPS(60);

	// Audio
	InitAudioDevice();
	scoreSound.Load("assets/score.mp3");
	gameOverSound.Load("assets/gameOver.mp3");
	
	// Values
	lastUpdateTime = 0;
	snake = Snake();
	food = new Food();
	running = true;
	score = 0;
}

void Game::Shutdown()
{
	CloseAudioDevice();
}

bool Game::shouldUpdate(double interval)
{
	double currentTime = GetTime();
	if (currentTime - lastUpdateTime >= interval) {
		lastUpdateTime = currentTime;
		return true;
	}
	return false;
}

void Game::HandleEvents()
{
	// Start again
	if (!running && IsKeyPressed(KEY_SPACE)) {
		score = 0;
		running = true;
	}

	// Change Direction
	if (IsKeyPressed(KEY_UP)    && snake.getLastMovement() != 'd') { snake.setDirection( { 0,-1 }); }
	if (IsKeyPressed(KEY_DOWN)  && snake.getLastMovement() != 'u') { snake.setDirection( { 0,1 });  }
	if (IsKeyPressed(KEY_LEFT)  && snake.getLastMovement() != 'r') { snake.setDirection({ -1,0 });  }
	if (IsKeyPressed(KEY_RIGHT) && snake.getLastMovement() != 'l') { snake.setDirection( { 1,0 });  }

	// Eat Food
	if (snake.getHeadPos() == food->getPosition()) {
		snake.Grow();
		food->changePosition(snake.getBody());
		score++;
		scoreSound.Play();
	}

	// Edges
	if (snake.getHeadPos().x >= kCellCount || snake.getHeadPos().x < 0
		|| snake.getHeadPos().y >= kCellCount || snake.getHeadPos().y < 0) {
		GameOver();
	}

	// Head-Tail Collision
	std::deque<RVector2> headlessBody = snake.getBody();
	headlessBody.pop_front();
	for (auto& segment : headlessBody) {
		if (segment == snake.getHeadPos()) {
			GameOver();
		}
	}
}

void Game::Update()
{
	if (shouldUpdate(0.2)) { snake.Update(); }
}

void Game::Draw()
{
	window.BeginDrawing();

		window.ClearBackground(kColorGreen);
		
		DrawRectangleLinesEx(RRectangle((float)kOffset - 5, (float)kOffset - 5, (float)kScreenSize + 10, (float)kScreenSize + 10), 5, kColorDarkGreen);
		RText(GetFontDefault(), "Snake", 40, 10.f, kColorDarkGreen).Draw(kOffset - 5, 20);
		RText(GetFontDefault(), "Score: " + std::to_string(score), 40, 10.f, kColorDarkGreen).Draw(kOffset - 5, kScreenSize + kOffset + 10);

		if (running) {
			food->Draw();
			snake.Draw();
		}
		else {
			RText text(GetFontDefault(), "GAME OVER", 70, 10.f, WHITE);
			int measure = text.Measure() / 2;
			int xPos = kScreenSize / 2 - measure;
			int yPos = kScreenSize / 2 - (int)text.GetFontSize() / 2;
			text.Draw(xPos + kOffset, yPos + kOffset);

			text = RText(GetFontDefault(), "PRESS SPACE TO RESTART", 30, 10.f, WHITE);
			measure = (int)(text.Measure() / 1.5);
			xPos = kScreenSize / 2 - measure;
			yPos = kScreenSize / 2 + (int)text.GetFontSize();
			text.Draw(xPos + kOffset, yPos + kOffset);
		}

	window.EndDrawing();
}

void Game::GameOver()
{
	gameOverSound.Play();
	snake.Reset();
	food->changePosition(snake.getBody());
	running = false;
}
