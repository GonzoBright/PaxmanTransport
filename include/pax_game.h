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

#include <pax_sprite.h>
#include <pax_glsl.h>
#include <pax_gltexture.h>

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
	float time;

	// Temporary members
	Sprite sprite;

	GLSLProgram colour_program;

	// character_standing
	GLTexture player_texture;

	const char* colour_program_vert_file;
	const char* colour_program_frag_file;
	const char* vertex_position_attrib_name;

	void Initialise();
	void InitialiseShaders();
	void GameLoop();
	void HandleInput();
	void Render();

public:
	Game();
	~Game();

	void Run();
};

#endif