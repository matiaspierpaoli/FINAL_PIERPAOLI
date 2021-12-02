#pragma once

#include <windows.h>
#include <vector>

#define WIDTH 50 // Set a width to a square in game
#define HEIGHT 25 // Set a height to a square in game

using namespace std;

class Snake
{
private:
    COORD pos; // Position
    int vel; // Velocity
    char dir; // Direction
    int len; // Lenght

    vector<COORD> body; // Body as vector         

public:
    Snake(COORD pos, float vel); // Constructor

    void grow(); // Increase lenght
    void move_snake(); // Change snake position
    void setDirection(char dir); // // Set new direction    
    void reset(); // Reset evrey value in snake

    char getDirection(); // // Get actual direction
    vector<COORD> get_body(); // Get vector
    COORD get_pos(); // Get actual position

    bool collided(); // Check collision with yourself
    bool eaten(COORD food); // // Check collision with fruit

   
};




