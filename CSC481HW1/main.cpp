#include "Game.h"
#include "Settings.h"
#include <Windows.h>

int main()
{
	if (!SHOW_CONSOLE)
	{
		ShowWindow(GetConsoleWindow(), SW_HIDE);
	}
	
	Game game;

	game.run();

	return 0;
}
