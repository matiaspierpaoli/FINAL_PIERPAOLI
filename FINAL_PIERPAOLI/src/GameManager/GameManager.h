#pragma once
#include <iostream>
#include <time.h>
#include <conio.h>
#include <vector>

#include "..\Snake\Snake.h"
#include "..\Fruit\Fruit.h"
#include "..\Menu\Menu.h"
#include "..\Credits\Credits.h"
#include "..\HowToPlay\HowToPlay.h"

namespace app
{
	using namespace std;

	enum class screenID // Every type of game screen
	{
		menu,
		levels,
		nonLevelSelected,
		easyLevel,
		mediumLevel,
		hardLevel,
		howToPlay,
		credits
	};

	struct Color // Every color without background
	{
		int black = 0;
		int	blue = 1;
		int	green = 2;
		int	cyan = 3;
		int	red = 4;
		int	magenta = 5;
		int	brown = 6;
		int	lightGray = 7;
		int	darkGray = 8;
		int	lightBlue = 9;
		int	lightGreen = 10;
		int	lightCyan = 11;
		int	lightRed =  12;
		int	lightMagenta = 13;
		int	yellow = 14;
		int	white = 15;

	};

	struct Levels // Types of levels
	{
		int easy;
		int medium;
		int hard;
	};

	// Creating extern variables that will be used in multiples methods across different .cpp and .h under namespace app, this way this variables will not overwrite themselves when GameManager.h is called more than once 
	extern screenID SIDMenu; // Screen Id in menu
	extern screenID SIDLevels; // Screen Id in levels
	extern bool exit; // Exit

	// Ints that increase or decrease depending on w or s input 
	extern int selectedItemIndexMenu; 
	extern int selectedItemIndexLevels;

	extern HANDLE windowHandle; // Used for SetConsoleTextAttribute()
	extern Color color; // Int that has all colors in struct Color

	class GameManager
	{
	private:
		
		// Objects
		Snake* snakeArray;
		Fruit* food;		

		// Struct objects
		Levels winCondition;
		Levels fruitsGrabbed;
		Levels maxTimer;
		Levels normalTimer;
		
		// Colors for SetConsoleTextAttribute()
		int const maxColors = 16;
		int randomColor;

		// Loss
		bool gameOverBool;
		bool collided;				

		// Win
		bool victory;

		// Pause
		bool pause;

		// Counter that automaticly increases every frame to lower a timer
		int framesCounter;

		// Amount of levels
		int const LEVELS_ARRAY_AMOUNT = 4;

		// Main game methods
		void resetGame();
		void gameOver();
		void update();
		void draw();

		// Controlles in game
		void showKeysGame();

		// Levels Screen
		void updateLevelsScreen();
		void drawLevelsScreen();

		void moveUpLevelsScreen(); // Input
		void moveDownLevelsScreen(); // Input

		// Main level methods
		void inputLevels();
		void updateLevels();
		void drawLevels();		
		
		// Method to hide cursor
		void set_cursor(bool visible);

	public:
		GameManager(); // Constructor
		~GameManager(); // Destructor
		void gameLoop(); // Main game loop called in main()
	};
}



