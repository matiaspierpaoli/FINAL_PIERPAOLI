#include "HowToPlay.h"
#include "..\GameManager\GameManager.h"

using namespace app;

namespace app
{
	namespace howToPlay
	{
		void updateHowToPlay()
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
		void drawHowToPlay()
		{
			SetConsoleTextAttribute(windowHandle, color.white); // Set a color to the text in console

			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 52, 4 }); // Set a cursor position
			cout << "Controlles:" << endl;

			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 40, 6 }); // Set a cursor position
			cout << "Move with: W - Up, A - Left, D - Right, S - Down" << endl;

			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 53, 8 }); // Set a cursor position
			cout << "P to pause" << endl;

			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 53, 12 }); // Set a cursor position
			cout << "Objective:" << endl;

			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 10, 14 }); // Set a cursor position
			cout << "Fruits will spawn randomly, grab 10 in easy mode, 15 in medium mode or 20 in hard mode in order to win" << endl;

			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 14, 16 }); // Set a cursor position
			cout << "But watch out! You have a certain time to do so, the harder the level the less time to grab one" << endl;

			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 53, 18 }); // Set a cursor position
			cout << "Good luck!" << endl;

			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 45,  27 }); // Set a cursor position
			cout << "Press ESC to return to menu" << endl;

			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 55, 29 }); // Set a cursor position
			cout << "V 1.0" << endl;
		}
	}
}