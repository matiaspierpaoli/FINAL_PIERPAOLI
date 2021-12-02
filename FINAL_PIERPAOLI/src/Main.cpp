#include "..\src\GameManager\GameManager.h"

/*
Matias Pierpaoli - Snake
Fundamentos de Programacion - Analisis de los Generos de Videjuegos
Final 2021

*/

using namespace app;

int main()
{
    srand(time(NULL));

    // An object is created, using a constructor, to call the main method that leads to all the other methods until exit = true
    GameManager* game = new GameManager();
    game->gameLoop();
    delete game; // Deleting the previous object to deallocat its memory

    // Finish program
    return 0;
}
