#include <iostream>
#include <raylib.h>
#include <deque>
#include <raymath.h>
#include "Game.h"
#include "Snake.h"
#include "Food.h"

using namespace std;

// Global variables
static bool allowMove = false;
Color green = { 173, 204, 96, 255 };
Color darkGreen = { 43, 51, 24, 255 };

// Constants
int cellSize = 30;
int cellCount = 25;
int offset = 75;

double lastUpdateTime = 0;

// Check if an element is present in a deque
bool ElementInDeque(Vector2 element, deque<Vector2> deque)
{
    for (unsigned int i = 0; i < deque.size(); i++)
    {
        if (Vector2Equals(deque[i], element))
        {
            return true;
        }
    }
    return false;
}

// Check if a certain amount of time has passed since the last update
bool EventTriggered(double interval)
{
    double currentTime = GetTime();
    if (currentTime - lastUpdateTime >= interval)
    {
        lastUpdateTime = currentTime;
        return true;
    }
    return false;
}

// Main function
int main()
{
    cout << "Starting the game..." << endl;
    InitWindow(2 * offset + cellSize * cellCount, 2 * offset + cellSize * cellCount, "Classic Snake ");
    SetTargetFPS(60);

    Game game = Game();
    // Main loop
    while (WindowShouldClose() == false)
    {
        BeginDrawing();

        if (EventTriggered(0.2)) // Update the game every 0.2 seconds
        {
            allowMove = true;
            game.Update();
        }

        if (IsKeyPressed(KEY_UP) && game.snake.direction.y != 1 && allowMove) // Change the direction of the snake
        {
            game.snake.direction = { 0, -1 };
            game.running = true;
            allowMove = false;
        }
        if (IsKeyPressed(KEY_DOWN) && game.snake.direction.y != -1 && allowMove)
        {
            game.snake.direction = { 0, 1 };
            game.running = true;
            allowMove = false;
        }
        if (IsKeyPressed(KEY_LEFT) && game.snake.direction.x != 1 && allowMove)
        {
            game.snake.direction = { -1, 0 };
            game.running = true;
            allowMove = false;
        }
        if (IsKeyPressed(KEY_RIGHT) && game.snake.direction.x != -1 && allowMove)
        {
            game.snake.direction = { 1, 0 };
            game.running = true;
            allowMove = false;
        }

        // Drawing
        ClearBackground(green);
        DrawRectangleLinesEx(Rectangle{ (float)offset - 5, (float)offset - 5, (float)cellSize * cellCount + 10, (float)cellSize * cellCount + 10 }, 5, darkGreen);
        DrawText("Classic Snake", offset - 5, 20, 40, darkGreen);
        DrawText(TextFormat("%i", game.score), offset - 5, offset + cellSize * cellCount + 10, 40, darkGreen);
        game.Draw();

        EndDrawing();
    }
    CloseWindow();
    return 0;
}
