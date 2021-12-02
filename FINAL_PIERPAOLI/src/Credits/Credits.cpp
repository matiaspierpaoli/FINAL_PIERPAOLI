#include "Credits.h"
#include "..\GameManager\GameManager.h"

using namespace app;

namespace app
{
	namespace credits
	{
		void updateCredits()
		{
			int input;

			if (_kbhit())
			{
				input = (char)_getch();

				if (input == 27) // If ESC is pressed return to menu
				{
					SIDMenu = screenID::menu;
					system("cls"); // Clear screen
				}				
			}
		}		
		void drawCredits()
		{
			SetConsoleTextAttribute(windowHandle, color.white); // Set a color to the text in console

			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 46, 10}); // Set a cursor position
			cout << "Made By: Pierpaoli Matias" << endl;

			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 45,  27 }); // Set a cursor position
			cout << "Press ESC to return to menu" << endl;

			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 55, 29 }); // Set a cursor position
			cout << "V 1.0" << endl;

			
		}
	}
}