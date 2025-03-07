#include <iostream>
#include <string>
#include "raylib.h"

using namespace std;

int main() {
	// Initialization
	int screenWidth = 800;
	int screenHeight = 450;

	InitWindow(screenWidth, screenHeight, "Physics Simulation");
	SetTargetFPS(60);

	// Ball
	Vector2 ballPos = { 400, 200 };

	// Gravity
	float gravity = 0.5f;
	float velocitY = 0.0f; // Vertical speed
	Vector2 Velocity = { 0.0f, 0.0f };
	float acceleration = 0.1f;
	bool isJump = false;

	// **Camera Setup**
	Camera2D camera = { 0 };
	camera.target = ballPos;      // Camera follows the ball
	camera.offset = { screenWidth / 2.0f, screenHeight / 2.0f }; // Center the camera
	camera.rotation = 0.0f;
	camera.zoom = 1.0f;           // Adjust zoom if needed

	while (!WindowShouldClose()) {
		// Uncomment the bello commented code to enable gravity and ball movements with acceleration

		Velocity.y += gravity; // Gravity
		ballPos.y += Velocity.y; // Ball falling
		// Ball movements

		if (IsKeyDown(KEY_A)) Velocity.x -= acceleration;
		else if (IsKeyDown(KEY_D)) Velocity.x += acceleration;
		/*else if (IsKeyDown(KEY_W)) Velocity.y -= acceleration; // These two movements are not needed when we have jump and they will also not work because of gravity.
		else if (IsKeyDown(KEY_S)) Velocity.y += acceleration;*/
		else if (IsKeyPressed(KEY_SPACE) && !isJump) {
			isJump = true;
			Velocity.y = -10.0f;
		}

		ballPos.x += Velocity.x;
		ballPos.y += Velocity.y;

		/*if (IsKeyDown(KEY_A)) ballPos.x -= 5;
		if (IsKeyDown(KEY_D)) ballPos.x += 5;
		if (IsKeyDown(KEY_W)) ballPos.y -= 5;
		if (IsKeyDown(KEY_S)) ballPos.y += 5;*/

		// Creating Boundries and inverting the velocity to make it bounce.
        
		if (ballPos.x <= 20) {
			ballPos.x = 20;
			Velocity.x = -Velocity.x;
		}
		if (ballPos.x >= 780) {
			ballPos.x = 780;
			Velocity.x = -Velocity.x;
		}
		if (ballPos.y >= 430) {
			isJump = false;
			ballPos.y = 430;
			//Velocity.y = 0.0f;
			Velocity.y = -Velocity.y;
		}
		if (ballPos.y <= 20) {
			ballPos.y = 20;
			Velocity.y = -Velocity.y;
		}

		cout << "Ball Position: " << ballPos.x << ", " << ballPos.y << endl;

		camera.target = ballPos;

		ClearBackground(WHITE);

		BeginDrawing(); // Starting Drawing
		//BeginMode2D(camera);

		DrawCircle(ballPos.x, ballPos.y, 20, RED);
		DrawRectangle(0, -20, 800, 20, BLACK); // Top border
		DrawRectangle(0, 450, 800, 20, BLACK); // Bottom border
		DrawRectangle(-20, -20, 20, 490, BLACK); // Left border
		DrawRectangle(800, -20, 20, 490, BLACK); // Right border

		//EndMode2D();
		EndDrawing(); // Ending Drawing
	}
	return 0;
}
