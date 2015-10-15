/******************************************************************************
*   pax_game.h
*
*	Handles basic game functions.
******************************************************************************/

#ifndef PAX_GAME_H
#define PAX_GAME_H

#include <iostream>
#include <SDL/SDL.h>
#include <GL/glew.h>

// Clean these up if possible
enum class GameState {
	GAME_PLAY,
	GAME_EXIT,
};

class Game {
private:
	SDL_Window* window;
	int width;
	int height;
	GameState game_state;

	// Temporary Functions
	void FatalError(char* error_string);

	void Initialise();
	void GameLoop();
	void HandleInput();
	void Render();

public:
	Game();
	~Game();

	void Run();
};

#endif