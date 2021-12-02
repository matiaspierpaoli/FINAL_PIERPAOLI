#include "Snake.h"
#include "..\GameManager\GameManager.h"

Snake::Snake(COORD pos, float vel) // Constructor
{
    this->pos = pos; // Set position
    this->vel = vel; // Set velocity

    dir = 'n'; // Initialize direction in "void"
    len = 1; // Initialize lenght in 1

    body.push_back(pos); // Push to the back of the vector a single value
}

void Snake::grow()
{
    len++; // Increase lenght
}

void Snake::move_snake() // Change snake position
{
    switch (dir) // Depending on direction change pos.X or pos.Y using velocity
    {
    case 'u': pos.Y -= vel; break;
    case 'd': pos.Y += vel; break;
    case 'l': pos.X -= vel; break;
    case 'r': pos.X += vel; break;
    }

    if (pos.X > WIDTH - 2) pos.X = 1; // If snake collides with right wall spawn in left wall
    if (pos.X < 1) pos.X = WIDTH - 2; // If snake collides with left wall spawn in left right
    if (pos.Y > HEIGHT - 2) pos.Y = 1; // If snake collides with floor spawn in ceiling
    if (pos.Y < 1) pos.Y = HEIGHT - 2; // If snake collides with ceiling spawn in floor

    body.push_back(pos); // Increase vector
    if (body.size() > len) body.erase(body.begin()); // Erase the previous value in vector to stop increasing length evrey move
}

void Snake::setDirection(char dir) 
{ 
    this->dir = dir; // Set new direction
}

void Snake::reset()
{
    len = 1; // Reset Lenght
    dir = 'n'; // Reset direction
    body.clear(); // Reset vector, not eliminating it
    pos = COORD{ WIDTH / 2, HEIGHT / 2 }; // Reset position
    body.push_back(pos); // Set again a single value to the vector
}

char Snake::getDirection()
{
    return dir; // Get actual direction
}

vector<COORD> Snake::get_body()
{
    return body; // Get vector
}

COORD Snake::get_pos() 
{ 
    return pos; // Get actual position
}

bool Snake::collided()
{
    // Collision with yourself
    for (int i = 0; i < len - 1; i++)
    {
        if (pos.X == body[i].X && pos.Y == body[i].Y) return true;
    }
    return false;
}

bool Snake::eaten(COORD food)
{
    if (pos.X == food.X && pos.Y == food.Y) return true; // Collision with fruit
    return false;
}

        
    


