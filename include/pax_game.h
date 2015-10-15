#ifndef PAX_GAME_H
#define PAX_GAME_H

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

	void Initialise();
	void GameLoop();
	void HandleInput();

public:
	Game();
	~Game();

	void Run();
};

#endif