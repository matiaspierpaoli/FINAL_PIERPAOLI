#pragma once

namespace app
{
	namespace menu
	{				
		// Amount of options to select in menu
		int const MENU_ARRAY_AMOUNT = 4;
				
		// Input and update
		void updateMenu();

		// Draw
		void drawMenu();

		void moveUpMenu(); // W input
		void moveDownMenu(); // S input
		void showKeysMenu(); // Contolles in menu		
	}	
}




	







