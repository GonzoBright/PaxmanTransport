#include <iostream>
#include <pax_game.h>

int main(int argc, char** argv)
{
	Game nGame;
	nGame.Run();

	std::cout << "Press any key to continue...";
	char a;
	std::cin >> a;

	return 0;
}