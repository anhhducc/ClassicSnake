#include "Food.h"
#include <raylib.h>
#include <deque>

extern bool ElementInDeque(Vector2 element, std::deque<Vector2> deque); // Function declaration
extern int cellSize; // Variable declaration
extern int offset;
extern int cellCount;

// Constructor: initialize the food with a random position and load its texture
Food::Food(std::deque<Vector2> snakeBody)
{
    Image image = LoadImage("Graphics/food.png");
    texture = LoadTextureFromImage(image);
    UnloadImage(image);
    position = GenerateRandomPos(snakeBody);
}

// Destructor: unload the texture of the food
Food::~Food()
{
    UnloadTexture(texture);
}

// Draw the food on the screen
void Food::Draw()
{
    DrawTexture(texture, offset + position.x * cellSize, offset + position.y * cellSize, WHITE);
}

// Generate a random cell on the grid
Vector2 Food::GenerateRandomCell()
{
    float x = GetRandomValue(0, cellCount - 1);
    float y = GetRandomValue(0, cellCount - 1);
    return Vector2{ x, y };
}

// Generate a random position for the food that is not occupied by the snake's body
Vector2 Food::GenerateRandomPos(std::deque<Vector2> snakeBody)
{
    Vector2 position = GenerateRandomCell();
    while (ElementInDeque(position, snakeBody))
    {
        position = GenerateRandomCell();
    }
    return position;
}
