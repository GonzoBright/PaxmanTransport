#include <pax_error.h>

#include <cstdlib>

#include <iostream>
#include <SDL/SDL.h>

void FatalError(std::string error_string)
{
	std::cout << std::string(error_string).c_str() << std::endl;
	std::cout << "Press any key to exit...";
	int temp;
	std::cin >> temp;
	SDL_Quit();
	exit(11);
}