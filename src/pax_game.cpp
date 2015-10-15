#include <pax_game.h>

Game::Game()
{
	this->window = nullptr;
	this->width = 1024;
	this->height = 768;
	this->game_state = GameState::GAME_PLAY;
}

Game::~Game() 
{
	
}

void Game::Run()
{
	Initialise();
	GameLoop();
}

void Game::Initialise()
{
	SDL_Init(SDL_INIT_EVERYTHING);

	// I don't quite like the newline
	this->window = SDL_CreateWindow("Paxman Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		width, height, SDL_WINDOW_OPENGL);
}

void Game::GameLoop()
{
	while (game_state != GameState::GAME_EXIT) {
		HandleInput();
	}
}

void Game::HandleInput()
{
	SDL_Event e;
	
	while (SDL_PollEvent(&e)) {
		switch (e.type) {
		case SDL_QUIT:
			this->game_state = GameState::GAME_EXIT;
			break;
		}
	}
}