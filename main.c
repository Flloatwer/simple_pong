#include "raylib/raylib.h"

void DrawStraightLine(int startx, int starty, int length, Color color) {
	DrawLine(startx, starty, startx, starty+length, color);
}

int main() {
	int x = 0;
	int y = 0;
	int xDirection = 0;
	int yDirection = 0;
	int score1 = 0;
	int score2 = 0;
	int player1pos = GetScreenHeight() / 2; // center the paddle
	int player2pos = GetScreenHeight() / 2; // center the paddle
	int fps = 149;
	int paddlesize = 120;
	int shouldIncrement1 = 0;
	int shouldIncrement2 = 0;
	// initialize the window and set the target FPS
	SetConfigFlags(FLAG_WINDOW_RESIZABLE);
	InitWindow(700, 700, "Pong Game by Flloatwer");
	SetTargetFPS(149);
	ClearBackground(BLACK);
	while (!WindowShouldClose())
	{
		// check and change the FPS if necessary
		if (IsKeyDown(KEY_I)) {
			fps++;
		} else if (IsKeyDown(KEY_K)) {
			fps--;
		}
		// check and change the paddlesize if necessary
		if (IsKeyDown(KEY_J)) {
			paddlesize--;
		} else if (IsKeyDown(KEY_U)) {
			paddlesize++;
		}
		SetTargetFPS(fps);
		BeginDrawing();
		// check if ball needs to change direction
		if (x == 0) {
			xDirection = 1;
		} else if (x == GetScreenWidth())
		{
			xDirection = -1;
		}
		if (y == 0) {
			yDirection = 1;
		} else if (y == GetScreenHeight())
		{
			yDirection = -1;
		}
		x += xDirection;
		y += yDirection;
		DrawRectangle(x, y, 5, 5, WHITE);
		// check for key presses and move the paddles
		if (IsKeyDown(KEY_W) && player1pos < GetScreenHeight() - 50 && player1pos >= 0) {
			player1pos -= 5;
		} else if (IsKeyDown(KEY_S) && player1pos < GetScreenHeight() - 50 && player1pos >= 0) {
			player1pos += 5;
		} else if (IsKeyDown(KEY_UP) && player2pos < GetScreenHeight() - 50 && player2pos >= 0) {
			player2pos -= 5;
		} else if (IsKeyDown(KEY_DOWN) && player2pos < GetScreenHeight() - 50 && player2pos >= 0) {
			player2pos += 5;
		}
		// check if paddle is out of bound and teleport if necessary
		if (player1pos < 0) {	// player 1
			player1pos = 0;
		} else if (player1pos > GetScreenHeight() - paddlesize) {
			player1pos = GetScreenHeight() - paddlesize;
		}
		if (player2pos < 0) {	// player 2
			player2pos = 0;
		} else if (player2pos > GetScreenHeight() - paddlesize) {
			player2pos = GetScreenHeight() - paddlesize;
		}
		// check for collision and increment score
		if (x == 0 && (y < player1pos || y > player1pos + paddlesize)) {
    		// Ball missed the paddle (blank area)
    		score2++;
		}
		if (x == GetScreenWidth() && (y < player2pos || y > player2pos + paddlesize)) {
    		// Ball missed the paddle (blank area)
    		score1++;
		}
		// increment score if needed
		// draw paddles and scores
		DrawRectangle(0, player1pos, 5, paddlesize, RED);
		DrawRectangle(GetScreenWidth() - 5, player2pos, 5, paddlesize, RED);
		DrawText(TextFormat("%d", score1), 10, 10, 50, YELLOW);
		DrawText(TextFormat("%d", score2), GetScreenWidth() - 35, 10, 50, YELLOW);
		// clear the screen and prepare for the next frame
		ClearBackground(BLACK);
		if (score1 == 10 || score2 == 10) {
			break; // end the game if one player reaches 10 points
		}
		EndDrawing();
	}
	CloseWindow();
	return 0;
} 