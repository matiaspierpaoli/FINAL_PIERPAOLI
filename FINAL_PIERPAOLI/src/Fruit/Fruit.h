#include <windows.h>
#include <cstdio>
#include <iostream>

#define WIDTH 50  // Set a width to a square in game
#define HEIGHT 25 // Set a height to a square in game

class Fruit
{
private:
    COORD pos; // Position

public:
    void gen_food(); // Generate food in random position between WIDTH and HEIGHT

    COORD get_pos(); // Get position
};
    

