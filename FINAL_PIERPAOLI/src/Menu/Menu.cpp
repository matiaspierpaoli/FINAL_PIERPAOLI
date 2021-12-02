#include "..\Menu\Menu.h"
#include "..\GameManager\GameManager.h"
	
using namespace app;

namespace app
{
	namespace menu
	{		
		void updateMenu()
		{
			int input; // Local variable

			if (_kbhit())
			{
				input = (char)_getch();

				if (input == 13) // If ENTER is pressed, depending on the selectedItemIndexMenu, switch to another screen or lead back to main and return 0
				{
					switch (selectedItemIndexMenu) 
					{
					case 0:
						SIDMenu = screenID::levels;
						system("cls");
						break;
					case 1:
						SIDMenu = screenID::howToPlay;
						system("cls");
						break;
					case 2:
						SIDMenu = screenID::credits;
						system("cls");
						break;
					case 3:
						exit = true;
						system("cls");
						SetConsoleTextAttribute(windowHandle, color.white);
						break;
					default:
						break;
					}
				}
				else if (input == 119) // W Key
				{
					moveUpMenu();
				}
				else if (input == 115) // S key
				{
					moveDownMenu();
				}
				else if (input == 27) // ESC
				{
					system("cls");
					exit = true;
				}
			}

		}

		void drawMenu()
		{
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 55, 5 }); // Set a cursor position
			SetConsoleTextAttribute(windowHandle, color.white); // Set a color to the text in console
			cout << "Snake" << endl;


			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 55, 12 }); // Set a cursor position
			if (selectedItemIndexMenu == 0) SetConsoleTextAttribute(windowHandle, color.red); // Set a color to the text in console
			else SetConsoleTextAttribute(windowHandle, color.white);
			cout << "Play" << endl;


			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 52, 14 }); // Set a cursor position
			if (selectedItemIndexMenu == 1) SetConsoleTextAttribute(windowHandle, color.red); // Set a color to the text in console
			else SetConsoleTextAttribute(windowHandle, color.white);
			cout << "How To Play" << endl;


			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 53, 16 }); // Set a cursor position
			if (selectedItemIndexMenu == 2) SetConsoleTextAttribute(windowHandle, color.red);  // Set a color to the text in console
			else SetConsoleTextAttribute(windowHandle, color.white);
			cout << "Credits" << endl;


			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 55, 18 }); // Set a cursor position
			if (selectedItemIndexMenu == 3) SetConsoleTextAttribute(windowHandle, color.red); // Set a color to the text in console
			else SetConsoleTextAttribute(windowHandle, color.white);
			cout << "Exit" << endl;

			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 55, 29 }); // Set a cursor position
			SetConsoleTextAttribute(windowHandle, color.white); // Set a color to the text in console
			cout << "V 1.0" << endl;

			showKeysMenu(); // Controlles in menu
		}

		void moveUpMenu()
		{
			if (selectedItemIndexMenu - 1 >= 0) // If selectedItemIndexMenu has not reached the minimum (0)
			{
				selectedItemIndexMenu--;
			}
		}

		void moveDownMenu()
		{
			if (selectedItemIndexMenu + 1 < MENU_ARRAY_AMOUNT) // If selectedItemIndexMenu has not reached the maximum (MENU_ARRAY_AMOUNT)
			{
				selectedItemIndexMenu++;
			}
		}			

		void showKeysMenu() // Controlles in menu
		{			
			SetConsoleTextAttribute(windowHandle, color.white); // Set a color to the text in console

			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 70, 12 }); // Set a cursor position
			cout << "W - Up" << endl;

			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 70, 14 }); // Set a cursor position	
			cout << "S - Down" << endl;

			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 70, 16 }); // Set a cursor position			
			cout << "ENTER - Enter" << endl;

			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 70, 18 }); // Set a cursor position
			cout << "ESC - Exit" << endl;

			
		}
	}
}



	





