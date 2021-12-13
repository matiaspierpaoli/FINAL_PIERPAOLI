#include "gamemanager.h"

using namespace app;
using namespace menu;
using namespace credits;
using namespace howToPlay;

namespace app
{
	bool exit = false; // Exit
	screenID SIDMenu = screenID::menu; // Set initial screenID SIDMenu in menu
	screenID SIDLevels = screenID::nonLevelSelected; // Set initial screenID SIDLevels in nonLevelSelected

	// Ints that increase or decrease depending on w or s input 
	int selectedItemIndexMenu = 0;
	int selectedItemIndexLevels = 0;

	HANDLE windowHandle = GetStdHandle(STD_OUTPUT_HANDLE); // Used for SetConsoleTextAttribute()
	Color color; // Int that has all colors in struct Color

	GameManager::GameManager()
	{
		// Initialize objects using respective constructors
		snakeArray = new Snake({ WIDTH / 2, HEIGHT / 2 }, 1.f);
		food = new Fruit();

		food->gen_food(); // Randomize first food

		// Initialize every win condition
		winCondition.easy = 10;
		winCondition.medium = 15;
		winCondition.hard = 20;

		// Initialize every fruitsGrabbed
		fruitsGrabbed.easy = 0;
		fruitsGrabbed.medium = 0;
		fruitsGrabbed.hard = 0;

		//fruitsGrabbed.easy = 7;
		//fruitsGrabbed.medium = 14; // -> Set more base fuits in order to win faster
		//fruitsGrabbed.hard = 19;

		// Initialize every maxTimer
		maxTimer.easy = 20;
		maxTimer.medium = 15;
		maxTimer.hard = 10;

		// Initialize every changing timer
		normalTimer.easy = maxTimer.easy;
		normalTimer.medium = maxTimer.medium;
		normalTimer.hard = maxTimer.hard;

		randomColor = 0; // Fist color as white

		// Bools
		gameOverBool = false;
		collided = false;
		victory = false;
		pause = false;

		framesCounter = 0;	// Frames counter


		set_cursor(false); // Hide cursor
	}

	GameManager::~GameManager()
	{
		// Deleting every objects to erase memory
		delete snakeArray;
		delete food;
	}

	void GameManager::gameLoop()
	{
		srand(static_cast<unsigned int>(time(nullptr))); // Set seed for rand()

		// Main game loop
		while (!exit) // While exit or ESC is not pressed in menu
		{
			draw();
			update();
		}
	}

	void GameManager::resetGame()
	{
		// Reset snake object
		snakeArray->reset();

		// Randomize a new food
		food->gen_food();

		// Reset bools
		gameOverBool = false;
		collided = false;
		victory = false;
		pause = false;

		framesCounter = 0; // Reset Frames counter

		// Reset Fruits grabbed
		fruitsGrabbed.easy = 0;
		fruitsGrabbed.medium = 0;
		fruitsGrabbed.hard = 0;

		//fruitsGrabbed.easy = 7;
		//fruitsGrabbed.medium = 14; // -> Set more base fuits in order to win faster in a reset game
		//fruitsGrabbed.hard = 19; 

		// Reset Normal timer
		normalTimer.easy = maxTimer.easy;
		normalTimer.medium = maxTimer.medium;
		normalTimer.hard = maxTimer.hard;

		SIDMenu = screenID::menu;
		SIDLevels = screenID::nonLevelSelected; // Reset screenID SIDLevels to no level selected
		selectedItemIndexLevels = 0; // Start input from the top in levels menu
	}

	void GameManager::gameOver()
	{
		resetGame();
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { WIDTH / 2 - 30, HEIGHT - 10 }); // Set Console Cursor Position
		system("pause"); // Pause screen waiting for input
		system("cls"); // Clear Screen	 
	}

	void GameManager::update()
	{
		switch (SIDMenu) // Depending on SIDMenu update the corresponding option in menu
		{
		case screenID::menu:
			updateMenu();
			break;
		case screenID::levels:
			switch (SIDLevels)
			{
			case screenID::nonLevelSelected:
				updateLevelsScreen();
				break;
			case screenID::easyLevel:
				inputLevels();
				updateLevels();
				break;
			case screenID::mediumLevel:
				inputLevels();
				updateLevels();
				break;
			case screenID::hardLevel:
				inputLevels();
				updateLevels();
				break;
			default:
				break;
			}
			break;
		case screenID::howToPlay:
			updateHowToPlay();
			break;
		case screenID::credits:
			updateCredits();
			break;
		default:
			break;
		}

	}

	void GameManager::draw()
	{
		Sleep(60); // Sleep Screen in order to see everything clearer

		switch (SIDMenu) // Depending on SIDMenu draw the corresponding option in menu
		{
		case screenID::menu:
			drawMenu();
			break;
		case screenID::levels:
			if (SIDLevels == screenID::nonLevelSelected) drawLevelsScreen();
			else
			{
				showKeysGame();
				drawLevels();
			}
			break;
		case screenID::howToPlay:
			drawHowToPlay();
			break;
		case screenID::credits:
			drawCredits();
			break;
		default:
			break;
		}
	}

	void GameManager::showKeysGame() // Show Keyboard inputs in a game
	{
		SetConsoleTextAttribute(windowHandle, color.green); // Set a color to the text in console
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { WIDTH + 30, 10 }); // Set a cursor position
		cout << "Move with: " << endl;

		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { WIDTH + 30, 12 }); // Set a cursor position
		cout << "W - Up" << endl;

		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { WIDTH + 30, 14 }); // Set a cursor position
		cout << "A - Left" << endl;

		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { WIDTH + 30, 16 }); // Set a cursor position
		cout << "D - Right" << endl;

		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { WIDTH + 30, 18 }); // Set a cursor position
		cout << "S - Down" << endl;

		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { WIDTH + 30, 20 }); // Set a cursor position
		cout << "P - pause" << endl;
	}

	void GameManager::updateLevelsScreen()
	{
		int input;

		if (_kbhit()) // Input in levels screen
		{
			input = (char)_getch();

			if (input == 13) // Enter
			{
				switch (selectedItemIndexLevels) // Set a new value to SIDLevels and clear screen
				{
				case 0:
					SIDLevels = screenID::easyLevel;
					system("cls");
					break;
				case 1:
					SIDLevels = screenID::mediumLevel;
					system("cls");
					break;
				case 2:
					SIDLevels = screenID::hardLevel;
					system("cls");
					break;
				case 3:
					SIDMenu = screenID::menu;
					system("cls");
					break;
				default:
					break;
				}
			}
			else if (input == 119) // W Key
			{
				moveUpLevelsScreen();
			}
			else if (input == 115) // S key
			{
				moveDownLevelsScreen();
			}
			else if (input == 27) // ESC
			{
				SIDMenu = screenID::menu;
				system("cls");
			}
		}
	}

	void GameManager::drawLevelsScreen()
	{
		// Draw levels screen

		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 50, 12 }); // Set a cursor position
		if (selectedItemIndexLevels == 0) SetConsoleTextAttribute(windowHandle, color.red); // Set a color to the text in console
		else SetConsoleTextAttribute(windowHandle, color.white);
		cout << "Easy Level " << endl;


		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 50, 14 }); // Set a cursor position
		if (selectedItemIndexLevels == 1) SetConsoleTextAttribute(windowHandle, color.red); // Set a color to the text in console
		else SetConsoleTextAttribute(windowHandle, color.white);
		cout << "Medium Level " << endl;


		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 50, 16 }); // Set a cursor position
		if (selectedItemIndexLevels == 2) SetConsoleTextAttribute(windowHandle, color.red); // Set a color to the text in console
		else SetConsoleTextAttribute(windowHandle, color.white);
		cout << "Hard Level " << endl;

		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 49, 24 }); // Set a cursor position
		if (selectedItemIndexLevels == 3) SetConsoleTextAttribute(windowHandle, color.red); // Set a color to the text in console
		else SetConsoleTextAttribute(windowHandle, color.white);
		cout << "Return to menu " << endl;
	}

	void GameManager::moveUpLevelsScreen()
	{
		if (selectedItemIndexLevels - 1 >= 0) // If selectedItemIndexLevels is on top stay on top
		{
			selectedItemIndexLevels--;
		}
	}
	void GameManager::moveDownLevelsScreen()
	{
		if (selectedItemIndexLevels + 1 < LEVELS_ARRAY_AMOUNT) // If selectedItemIndexLevels is at the bottom stay at the bottom
		{
			selectedItemIndexLevels++;
		}
	}

	void GameManager::inputLevels()
	{
		if (_kbhit())
		{
			switch (_getch()) // Depending on input set a new direction, pause, unpause or exit level
			{
			case 'w':
				if (!pause) snakeArray->setDirection('u');
				break;
			case 'a':
				if (!pause) snakeArray->setDirection('l');
				break;
			case 's':
				if (!pause) snakeArray->setDirection('d');
				break;
			case 'd':
				if (!pause) snakeArray->setDirection('r');
				break;
			case 'p':
				pause = !pause;
				system("cls");
				break;
			case 27:
				SIDMenu = screenID::menu;
				gameOver();
				system("cls");
				break;
			}
		}
	}

	void GameManager::updateLevels()
	{
		if (!gameOverBool && !victory) // If game is not finished
		{
			if (!pause) // If pause is not active
			{
				if (snakeArray->collided()) // Check collision with itself
				{
					// If collided() returns true 
					gameOverBool = true;
					collided = true;
				}

				if (snakeArray->eaten(food->get_pos())) // Check collision between snake and food
				{
					food->gen_food(); // Randomize food

					if (!victory) snakeArray->grow(); // If not every food is collected grow snake

					framesCounter = 0; // Reset frames counter to later on reset timer

					switch (SIDLevels) // Depending on the level selected add 1 to fruitsGrabbed and reset timer
					{
					case app::screenID::easyLevel:
						fruitsGrabbed.easy++;
						normalTimer.easy = maxTimer.easy;
						if (fruitsGrabbed.easy == winCondition.easy) victory = true;
						break;
					case app::screenID::mediumLevel:
						fruitsGrabbed.medium++;
						normalTimer.medium = maxTimer.medium;
						if (fruitsGrabbed.medium == winCondition.medium) victory = true;
						break;
					case app::screenID::hardLevel:
						fruitsGrabbed.hard++;
						normalTimer.hard = maxTimer.hard;
						if (fruitsGrabbed.hard == winCondition.hard) victory = true;
						break;
					default:
						break;
					}
				}

				snakeArray->move_snake(); // Snake movement

				framesCounter++;

				switch (SIDLevels) // Depending on the level selected substract 1 to normalTimer and if normalTimer is 0 finish game
				{
				case app::screenID::easyLevel:
					if (framesCounter % 13 == 0) normalTimer.easy--;
					if (normalTimer.easy == 0) gameOverBool = true;
					if (framesCounter == 143) system("cls"); // If timer is 10 clear screen to hide second index in numbers from 10 to 99
					// if (normalTimer.easy == 10) system("cls"); // Original idea that clears screen multiple times
					break;
				case app::screenID::mediumLevel:
					if (framesCounter % 13 == 0) normalTimer.medium--;
					if (normalTimer.medium == 0) gameOverBool = true;
					if (framesCounter == 78) system("cls");
					break;
				case app::screenID::hardLevel:
					if (framesCounter % 13 == 0) normalTimer.hard--;
					if (normalTimer.hard == 0) gameOverBool = true;
					if (framesCounter == 13) system("cls");
					break;
				default:
					break;
				}
			}
		}
		else gameOver();
	}

	void GameManager::drawLevels()
	{
		SetConsoleTextAttribute(windowHandle, color.blue); // Set a color to the text in console
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 0, 0 }); // Set a cursor position

		switch (SIDLevels) // Depending on the level draw fruitsGrabbed
		{
		case app::screenID::easyLevel:
			cout << "Fruits Grabbed : " << fruitsGrabbed.easy << endl;
			break;
		case app::screenID::mediumLevel:
			cout << "Fruits Grabbed : " << fruitsGrabbed.medium << endl;
			break;
		case app::screenID::hardLevel:
			cout << "Fruits Grabbed : " << fruitsGrabbed.hard << endl;
			break;
		default:
			break;
		}

		SetConsoleTextAttribute(windowHandle, color.red); // Set a color to the text in console
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 37, 27 }); // Set a cursor position

		switch (SIDLevels) // Depending on the level draw normalTimer
		{
		case app::screenID::easyLevel:
			cout << "Seconds Left : " << normalTimer.easy << endl;
			break;
		case app::screenID::mediumLevel:
			cout << "Seconds Left : " << normalTimer.medium << endl;
			break;
		case app::screenID::hardLevel:
			cout << "Seconds Left : " << normalTimer.hard << endl;
			break;
		default:
			break;
		}

		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 0, 2 }); // Set a cursor position

		for (int i = 0; i < HEIGHT; i++)
		{
			SetConsoleTextAttribute(windowHandle, randomColor); // Set a color to the text in console
			cout << "\t\t\t|"; // Left wall

			for (int j = 0; j < WIDTH - 2; j++)
			{
				do
				{
					randomColor = rand() % maxColors; // Randomize color
				} while (randomColor == 1); // Different from black


				if (i == 0 || i == HEIGHT - 1)
				{
					SetConsoleTextAttribute(windowHandle, randomColor); // Set a color to the text in console
					cout << '-'; // Top and bottom

				}
				else if (i == snakeArray->get_pos().Y && j + 1 == snakeArray->get_pos().X)
				{
					SetConsoleTextAttribute(windowHandle, color.yellow); // Set a color to the text in console
					cout << '^'; // Player head
				}
				else if (i == food->get_pos().Y && j + 1 == food->get_pos().X)
				{
					SetConsoleTextAttribute(windowHandle, color.magenta); // Set a color to the text in console
					cout << '@'; // Food					
				}
				else
				{
					bool isBodyPart = false;
					for (int k = 0; k < snakeArray->get_body().size() - 1; k++)
					{
						if (i == snakeArray->get_body()[k].Y && j + 1 == snakeArray->get_body()[k].X)
						{
							SetConsoleTextAttribute(windowHandle, color.yellow); // Set a color to the text in console
							cout << 'o'; // Player body
							isBodyPart = true;
							break;
						}
					}

					if (!isBodyPart) // If no snake body parts are there draw space, and if this is not done, right wall will be moved forward
					{
						SetConsoleTextAttribute(windowHandle, color.white); // Set a color to the text in console
						cout << ' ';
					}
				}
			}
			SetConsoleTextAttribute(windowHandle, randomColor);	 // Set a color to the text in console					
			cout << "|" << endl; // Right wall
		}

		if (pause) // If pause is active
		{
			SetConsoleTextAttribute(windowHandle, color.green); // Set a color to the text in console
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { WIDTH + 30, 4 }); // Set a cursor position
			cout << "PAUSED" << endl;
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { WIDTH + 30, 5 }); // Set a cursor position
			cout << "Direction: ";

			// Show direction that the snake will follow when pause is inactive (not able to change in pause mode)
			switch (snakeArray->getDirection())
			{
			case 'u': cout << "Up" << endl; break;
			case 'd': cout << "Down" << endl; break;
			case 'l': cout << "Left" << endl; break;
			case 'r': cout << "Right" << endl; break;
			}
		}

		if (victory) // If the player wins
		{
			SetConsoleTextAttribute(windowHandle, color.green); // Set a color to the text in console
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 10, 27 }); // Set a cursor position
			cout << "You won!: :)" << endl;
		}
		else if (gameOverBool) // If the player losses
		{
			SetConsoleTextAttribute(windowHandle, color.red); // Set a color to the text in console
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 0, 27 }); // Set a cursor position

			switch (SIDLevels) // Depending on the level selected draw the reason of the loss
			{
			case app::screenID::easyLevel:
				if (normalTimer.easy == 0) cout << "You ran out of time :( " << endl;
				else if (collided) cout << "Oh no you collided with yourself :( " << endl;
				else cout << "Wait what?? " << endl; // Not possible
				break;
			case app::screenID::mediumLevel:
				if (normalTimer.medium == 0) cout << "You ran out of time :( " << endl;
				else if (collided) cout << "Oh no you collided with yourself :( " << endl;
				else cout << "Wait what?? " << endl;  // Not possible
				break;
			case app::screenID::hardLevel:
				if (normalTimer.hard == 0) cout << "You ran out of time :( " << endl;
				else if (collided) cout << "Oh no you collided with yourself :( " << endl;
				else cout << "Wait what?? " << endl;  // Not possible
				break;
			default:
				break;
			}
		}
	}

	void GameManager::set_cursor(bool visible) // Credits to www.codegrepper.com/code-examples/cpp/c%2B%2B+hide+cursor
	{
		// Set bool parameter true to show cursor or false to hide it
		CONSOLE_CURSOR_INFO info;
		info.dwSize = 100;
		info.bVisible = visible;
		SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
	}
}
