#include "Snake.h"
#include <raylib.h>
#include <raymath.h>

extern int cellSize;// Variable declaration
extern int offset;
extern Color darkGreen;

// Draw the snake on the screen
void Snake::Draw()
{
    for (unsigned int i = 0; i < body.size(); i++)
    {
        float x = body[i].x;
        float y = body[i].y;
        Rectangle segment = Rectangle{ offset + x * cellSize, offset + y * cellSize, (float)cellSize, (float)cellSize };
        DrawRectangleRounded(segment, 0.5, 6, darkGreen);
    }
}

// Update the position of the snake based on its direction
void Snake::Update()
{
    body.push_front(Vector2Add(body[0], direction));
    if (addSegment == true)
    {
        addSegment = false;
    }
    else
    {
        body.pop_back();
    }
}

// Reset the snake to its initial state
void Snake::Reset()
{
    body = { Vector2{6, 9}, Vector2{5, 9}, Vector2{4, 9} };
    direction = { 1, 0 };
}
