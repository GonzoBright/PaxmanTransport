/******************************************************************************
*   pax_game.cpp
*
*	Handles basic game functions.
******************************************************************************/

#include <pax_game.h>
#include <pax_error.h>

Game::Game()
{
	this->window = nullptr;
	this->width = 1024;
	this->height = 768;
	this->game_state = GameState::GAME_PLAY;
	this->time = 0;
}

Game::~Game() 
{
}

void Game::Run()
{
	Initialise();
	this->sprite.Initialise(-1.0f, -1.0f, 2.0f, 2.0f);
	GameLoop();
}

void Game::Initialise()
{
	SDL_Init(SDL_INIT_EVERYTHING);

	//SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	//SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);

	// Create SDL Window
	this->window = SDL_CreateWindow("Paxman Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		width, height, SDL_WINDOW_OPENGL);
	if (this->window == nullptr) {
		FatalError("SDL: Failed to create window properly.");
	}

	// Create GLContext
	SDL_GLContext gl_context = SDL_GL_CreateContext(this->window);
	if (gl_context == nullptr) {
		FatalError("SDL_GL: Context failed to load properly.");
	}

	// Initialise GLEW
	glewExperimental = true;
	GLenum glew_result = glewInit();
	if (glew_result != GLEW_OK) {
		FatalError("GLEW: Failed to initialise GLEW.");
	}

	// Enable double-buffering
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	// Set background colour
	glClearColor(0.0f, 0.0f, 1.0f, 0.0f);

	// Initialise our shaders
	InitialiseShaders();
}

void Game::InitialiseShaders()
{
	const char* colour_program_vert_file = "../res/shaders/colour_shading.vert";
	const char* colour_program_frag_file = "../res/shaders/colour_shading.frag";
	const char* vertex_position_attrib_name = "vertexPosition";
	const char* colour_position_attrib_name = "vertexColour";
	colour_program.CompileShaders(colour_program_vert_file, colour_program_frag_file);
	colour_program.AddAttribute(vertex_position_attrib_name);
	colour_program.AddAttribute(colour_position_attrib_name);
	colour_program.LinkShaders();
}

void Game::GameLoop()
{
	while (game_state != GameState::GAME_EXIT) {
		HandleInput();
		time += 0.005;
		Render();
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
		case SDL_MOUSEMOTION:
			// Bits and pieces for MOUSEMOTION
			break;
		}
	}
}

void Game::Render()
{
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	colour_program.Use();

	// must set uniform(s) before rendering
	// get rid of this madness
	char* tmp = "time";
	GLuint time_location = colour_program.GetUniformLocation(tmp);
	glUniform1f(time_location, this->time);

	this->sprite.Draw();

	colour_program.Disuse();

	SDL_GL_SwapWindow(this->window);
}
