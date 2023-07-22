#include "Game.h"
#include "Snake.h"
#include "Food.h"
#include <raylib.h>
#include <deque>
#include <raymath.h>

extern bool ElementInDeque(Vector2 element, std::deque<Vector2> deque);// Function declaration
extern int cellCount;// Variable declaration

// Constructor: initialize the game and load its sounds
Game::Game()
{
    InitAudioDevice();
    eatSound = LoadSound("Sounds/eat.mp3");
    wallSound = LoadSound("Sounds/wall.mp3");
}

// Destructor: unload the sounds of the game
Game::~Game()
{
    UnloadSound(eatSound);
    UnloadSound(wallSound);
    CloseAudioDevice();
}

// Draw the game on the screen
void Game::Draw()
{
    food.Draw();
    snake.Draw();
}

// Update the state of the game
void Game::Update()
{
    if (running)
    {
        snake.Update();
        CheckCollisionWithFood();
        CheckCollisionWithEdges();
        CheckCollisionWithTail();
    }
}

// Check if the snake has collided with the food
void Game::CheckCollisionWithFood()
{
    if (Vector2Equals(snake.body[0], food.position))
    {
        food.position = food.GenerateRandomPos(snake.body);
        snake.addSegment = true;
        score++;
        PlaySound(eatSound);
    }
}

// Check if the snake has collided with the edges of the screen
void Game::CheckCollisionWithEdges()
{
    if (snake.body[0].x == cellCount || snake.body[0].x == -1)
    {
        GameOver();
    }
}

// Check if the snake has collided with its own tail
void Game::CheckCollisionWithTail()
{
    std::deque<Vector2> headlessBody = snake.body;
    headlessBody.pop_front();
    if (ElementInDeque(snake.body[0], headlessBody))
    {
        GameOver();
    }
}

// End the game and reset its state
void Game::GameOver()
{
    snake.Reset();
    food.position = food.GenerateRandomPos(snake.body);
    running = false;
    score = 0;
    PlaySound(wallSound);
}
