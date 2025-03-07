#include <iostream>
#include <cmath>
#include <vector>
#include "raylib.h"

using namespace std;

struct Ball {
	Vector2 position;
	Vector2 velocity;
	float radius;
	Color color;
};

void HandleBallCollision(vector<Ball> &balls){
	for (int i = 0; i < balls.size(); i++) {
		for (int j = i + 1; j < balls.size(); j++) {
			Ball& ball1 = balls[i];
			Ball& ball2 = balls[j];

			/*float distance = sqrt(pow(balls[i].position.x - balls[j].position.x, 2) + pow(balls[i].position.y - balls[j].position.y, 2));
			if (distance <= balls[i].radius + balls[j].radius) {
				Vector2 temp = balls[i].velocity;
				balls[i].velocity = balls[j].velocity;
				balls[j].velocity = temp;
			}*/
			if (CheckCollisionCircles(ball1.position, ball1.radius, ball2.position, ball2.radius)) {
				Vector2 temp = ball1.velocity;
				ball1.velocity = ball2.velocity;
				ball2.velocity = temp;
			}
		}
	}
}

int main() {
	// Initialization
	int screenWidth = 800;
	int screenHeight = 450;

	InitWindow(screenWidth, screenHeight, "Physics Simulation");
	SetTargetFPS(60);

	// Ball
	/*Vector2 ballPos = { 400, 200 };*/
	
	vector<Ball> balls = {
		{ {400, 200}, {0.0f, 0.0f}, 20, RED },
		{ {200, 200}, {0.0f, 0.0f}, 20, BLUE },
		{ {600, 200}, {0.0f, 0.0f}, 20, GREEN },
		{ {400, 100}, {0.0f, 0.0f}, 20, YELLOW },
		{ {400, 300}, {0.0f, 0.0f}, 20, ORANGE },
		{ { 400, 200 }, {0.0f, 0.0f}, 20, RED },
		{ {200, 200}, {0.0f, 0.0f}, 20, BLUE },
		{ {600, 200}, {0.0f, 0.0f}, 20, GREEN }
	};

	// Gravity
	float gravity = 0.5f;
	float acceleration = 0.1f;
	bool isJump = false;

	// **Camera Setup**
	//Camera2D camera = { 0 };
	//camera.target = ballPos;      // Camera follows the ball
	//camera.offset = { screenWidth / 2.0f, screenHeight / 2.0f }; // Center the camera
	//camera.rotation = 0.0f;
	//camera.zoom = 1.0f;          
	// // Adjust zoom if needed

	while (!WindowShouldClose()) {
		// Uncomment the bello commented code to enable gravity and ball movements with acceleration


		for(Ball &ballPos : balls)
		{
			ballPos.velocity.y += gravity; // Gravity
			ballPos.position.y += ballPos.velocity.y; // Ball falling
			ballPos.position.x += ballPos.velocity.x;
			// Ball movements

			if (IsKeyDown(KEY_A)) ballPos.velocity.x -= acceleration;
			else if (IsKeyDown(KEY_D)) ballPos.velocity.x += acceleration;  
			/*else if (IsKeyDown(KEY_W)) Velocity.y -= acceleration; // These two movements are not needed when we have jump and they will also not work because of gravity.
			else if (IsKeyDown(KEY_S)) Velocity.y += acceleration;*/
			else if (IsKeyPressed(KEY_SPACE) && !isJump) {
				isJump = true;
				ballPos.velocity.y = -10.0f; 
			}

			ballPos.position.x += ballPos.velocity.x;
			ballPos.position.y += ballPos.velocity.y;

			/*if (IsKeyDown(KEY_A)) ballPos.x -= 5;
			if (IsKeyDown(KEY_D)) ballPos.x += 5;
			if (IsKeyDown(KEY_W)) ballPos.y -= 5;
			if (IsKeyDown(KEY_S)) ballPos.y += 5;*/

			// Creating Boundries
			if (ballPos.position.x <= 20) {
				ballPos.position.x = 20;
				ballPos.velocity.x = -ballPos.velocity.x;
			}
			if (ballPos.position.x >= 780) {
				ballPos.position.x = 780;
				ballPos.velocity.x = -ballPos.velocity.x;
			}
			if (ballPos.position.y >= 430) {
				isJump = false;
				ballPos.position.y = 430;
				//Velocity.y = 0.0f;
				ballPos.velocity.y = -ballPos.velocity.y;
			}
			if (ballPos.position.y <= 20) {
				ballPos.position.y = 20;
				ballPos.velocity.y = -ballPos.velocity.y;
			}
		}


		//cout << "Ball Position: " << ballPos.x << ", " << ballPos.y << endl;

		//camera.target = ballPos;

		HandleBallCollision(balls);

		BeginDrawing(); // Starting Drawing
		ClearBackground(WHITE); // Clear the screen
		//BeginMode2D(camera);

		//DrawCircle(30, 30, 20, RED); // Ball
		DrawRectangle(0, -20, 800, 20, BLACK); // Top border
		DrawRectangle(0, 450, 800, 20, BLACK); // Bottom border
		DrawRectangle(-20, -20, 20, 490, BLACK); // Left border
		DrawRectangle(800, -20, 20, 490, BLACK); // Right border

		for (const Ball &ballPos : balls)
		{
			DrawCircle(ballPos.position.x, ballPos.position.y, ballPos.radius, ballPos.color);
		}
		//EndMode2D();
		EndDrawing(); // Ending Drawing
	}
	return 0;
}
