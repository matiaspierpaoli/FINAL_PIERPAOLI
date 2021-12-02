#include "Fruit.h"
#include <time.h>

void Fruit::gen_food() // Generate food in random position between WIDTH and HEIGHT
{   
    do
    {
        pos.X = rand() % WIDTH + 1;
        pos.Y = rand() % HEIGHT + 1;

    } while (pos.X >= WIDTH - 1 || pos.X <= 0 || pos.Y <= 0 || pos.Y >= HEIGHT - 1);
}

COORD Fruit::get_pos() 
{
    return pos; // Get position
}
    


