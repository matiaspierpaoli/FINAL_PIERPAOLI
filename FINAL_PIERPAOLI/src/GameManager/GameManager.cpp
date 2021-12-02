#include "gamemanager.h"

using namespace app;
using namespace menu;
using namespace credits;
using namespace howToPlay;

namespace app
{
	bool exit = false;
	screenID SIDMenu = screenID::menu;
	screenID SIDLevels = screenID::nonLevelSelected;
	int selectedItemIndexMenu = 0;
	int selectedItemIndexLevels = 0;
	HANDLE windowHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	Color color;	

	GameManager::GameManager()
	{
		snakeArray = new Snake({ WIDTH / 2, HEIGHT / 2 }, 1.f);
		food = new Fruit();

		food->gen_food();

		winCondition.easy = 10;
		winCondition.medium = 15;
		winCondition.hard = 20;

		fruitsGrabbed.easy = 0;
		fruitsGrabbed.medium = 0;
		fruitsGrabbed.hard = 0;

		//fruitsGrabbed.easy = 7;
		//fruitsGrabbed.medium = 14; // -> Set more base fuits to win faster
		//fruitsGrabbed.hard = 19;

		maxTimer.easy = 20;
		maxTimer.medium = 15;
		maxTimer.hard = 10;

		normalTimer.easy = maxTimer.easy;
		normalTimer.medium = maxTimer.medium;
		normalTimer.hard = maxTimer.hard;

		randomColor = 0;

		gameOverBool = false;
		collided = false;		
		victory = false;
		pause = false;
		
		framesCounter = 0;	

		
		set_cursor(false);
	}

	GameManager::~GameManager()
	{
		delete snakeArray;
		delete food;
	}

	void GameManager::gameLoop()
	{
		srand(static_cast<unsigned int>(time(nullptr)));

		// Main game loop
		while (!exit)
		{
			draw();
			update();
		}
	}

	void GameManager::resetGame()
	{
		snakeArray->reset();
		food->gen_food();
		
		gameOverBool = false;
		collided = false;
		victory = false;
		pause = false;
		
		framesCounter = 0;

		fruitsGrabbed.easy = 0;
		fruitsGrabbed.medium = 0;
		fruitsGrabbed.hard = 0;

		//fruitsGrabbed.easy = 7;
		//fruitsGrabbed.medium = 14; // -> Set more base fuits to win faster
		//fruitsGrabbed.hard = 19; 
		
		normalTimer.easy = maxTimer.easy;
		normalTimer.medium = maxTimer.medium;
		normalTimer.hard = maxTimer.hard;

		SIDLevels = screenID::nonLevelSelected;
		selectedItemIndexLevels = 0;
	}

	void GameManager::gameOver()
	{
		resetGame();
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { WIDTH / 2 - 30, HEIGHT - 10 });
		system("pause");
		system("cls");
		SIDMenu = screenID::menu;
	}

	void GameManager::update()
	{		
		switch (SIDMenu)
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
		Sleep(60);

		switch (SIDMenu)
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

	void GameManager::showKeysGame()
	{
		SetConsoleTextAttribute(windowHandle, color.green);
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { WIDTH + 30, 10 });
		cout << "Move with: " << endl;
		
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { WIDTH + 30, 12 });
		cout << "W - Up" << endl;
		
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { WIDTH + 30, 14 });
		cout << "A - Left" << endl;
		
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { WIDTH + 30, 16 });
		cout << "D - Right" << endl;
		
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { WIDTH + 30, 18 });
		cout << "S - Down" << endl;

		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { WIDTH + 30, 20 });
		cout << "P - pause" << endl;
	}

	void GameManager::updateLevelsScreen()
	{		
		int input;

		if (_kbhit())
		{
			input = (char)_getch();

			if (input == 13)
			{
				switch (selectedItemIndexLevels)
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
			else if (input == 119) // A Key
			{
				moveUpLevelsScreen();
			}
			else if (input == 115) // D key
			{
				moveDownLevelsScreen();
			}
			else if (input == 27)
			{				
				SIDMenu = screenID::menu;
				system("cls");
			}
		}
	}

	void GameManager::drawLevelsScreen()
	{
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 50, 12 });
		if (selectedItemIndexLevels == 0) SetConsoleTextAttribute(windowHandle, color.red);
		else SetConsoleTextAttribute(windowHandle, color.white);
		cout << "Easy Level " << endl;


		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 50, 14 });
		if (selectedItemIndexLevels == 1) SetConsoleTextAttribute(windowHandle, color.red);
		else SetConsoleTextAttribute(windowHandle, color.white);
		cout << "Medium Level " << endl;


		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 50, 16 });
		if (selectedItemIndexLevels == 2) SetConsoleTextAttribute(windowHandle, color.red);
		else SetConsoleTextAttribute(windowHandle, color.white);
		cout << "Hard Level " << endl;	
		
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 49, 24 });
		if (selectedItemIndexLevels == 3) SetConsoleTextAttribute(windowHandle, color.red);
		else SetConsoleTextAttribute(windowHandle, color.white);
		cout << "Return to menu " << endl;
	}

	void GameManager::moveUpLevelsScreen()
	{
		if (selectedItemIndexLevels - 1 >= 0)
		{
			selectedItemIndexLevels--;
		}
	}
	void GameManager::moveDownLevelsScreen()
	{
		if (selectedItemIndexLevels + 1 < LEVELS_ARRAY_AMOUNT)
		{
			selectedItemIndexLevels++;
		}
	}

	void GameManager::inputLevels()
	{		
		if (_kbhit())
		{
			switch (_getch())
			{
			case 'w': 
				if(!pause) snakeArray->setDirection('u');
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
		if (!gameOverBool && !victory)
		{
			if (!pause)
			{
				if (snakeArray->collided())
				{
					gameOverBool = true;
					collided = true;
				}

				if (snakeArray->eaten(food->get_pos()))
				{
					food->gen_food();
					if (!victory) snakeArray->grow();	
					framesCounter = 0;
					
					switch (SIDLevels)
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

				snakeArray->move_snake();
				framesCounter++;

				switch (SIDLevels)
				{
				case app::screenID::easyLevel:
					if (framesCounter % 13 == 0) normalTimer.easy--;
					if (normalTimer.easy == 0) gameOverBool = true;
					if (framesCounter == 143) system("cls");
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
		SetConsoleTextAttribute(windowHandle, color.blue);
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 0, 0 });

		switch (SIDLevels)
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

		SetConsoleTextAttribute(windowHandle, color.red);
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 37, 27 });
		switch (SIDLevels)
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
		
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 0, 2 });
		
		for (int i = 0; i < HEIGHT; i++)
		{											
			SetConsoleTextAttribute(windowHandle, randomColor);
			cout << "\t\t\t|";

			for (int j = 0; j < WIDTH - 2; j++)
			{		
				do
				{
					randomColor = rand() % maxColors;
				} while (randomColor == 1); // Different from black
				

				if (i == 0 || i == HEIGHT - 1)
				{					
					SetConsoleTextAttribute(windowHandle, randomColor);
					cout << '-';
										
				}
				else if (i == snakeArray->get_pos().Y && j + 1 == snakeArray->get_pos().X)
				{
					SetConsoleTextAttribute(windowHandle, color.yellow);
					cout << '^';
				}
				else if (i == food->get_pos().Y && j + 1 == food->get_pos().X)
				{
					SetConsoleTextAttribute(windowHandle, color.magenta);
					cout << '@';					
				} 
				else
				{
					bool isBodyPart = false;
					for (int k = 0; k < snakeArray->get_body().size() - 1; k++)
					{
						if (i == snakeArray->get_body()[k].Y && j + 1 == snakeArray->get_body()[k].X)
						{
							SetConsoleTextAttribute(windowHandle, color.yellow);
							cout << 'o';
							isBodyPart = true;
							break;
						}
					}

					if (!isBodyPart)
					{
						SetConsoleTextAttribute(windowHandle, color.white);
						cout << ' ';						
					}					
				}
			}			
			SetConsoleTextAttribute(windowHandle, randomColor);						
			cout << "|" << endl;
		}			

		if (pause)
		{
			SetConsoleTextAttribute(windowHandle, color.green);
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { WIDTH + 30, 4 });
			cout << "PAUSED" << endl;
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { WIDTH + 30, 5 });
			cout << "Direction: ";
						
			switch (snakeArray->getDirection())
			{
			case 'u': cout << "Up" << endl; break;
			case 'd': cout << "Down" << endl; break;
			case 'l': cout << "Left" << endl; break;
			case 'r': cout << "Right" << endl; break;
			}
		}
		
		if (victory)
		{
			SetConsoleTextAttribute(windowHandle, color.green);
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 10, 27 });
			cout << "You won!: :)" << endl;
		}
		else if (gameOverBool)
		{
			SetConsoleTextAttribute(windowHandle, color.red);
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 0, 27 });
			switch (SIDLevels)
			{
			case app::screenID::easyLevel:
				if (normalTimer.easy == 0) cout << "You ran out of time :( " << endl;
				else if (collided) cout << "Oh no you collided with yourself :( " << endl;
				else cout << "Wait what?? " << endl;
				break;
			case app::screenID::mediumLevel:
				if (normalTimer.medium == 0) cout << "You ran out of time :( " << endl;
				else if (collided) cout << "Oh no you collided with yourself :( " << endl;
				else cout << "Wait what?? " << endl;
				break;
			case app::screenID::hardLevel:
				if (normalTimer.hard == 0) cout << "You ran out of time :( " << endl;
				else if (collided) cout << "Oh no you collided with yourself :( " << endl;
				else cout << "Wait what?? " << endl;
				break;
			default:
				break;
			}			
		}		
	}

	void GameManager::set_cursor(bool visible) 
	{
		CONSOLE_CURSOR_INFO info;
		info.dwSize = 100;
		info.bVisible = visible;
		SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
	}
}
