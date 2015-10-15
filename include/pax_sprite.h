/******************************************************************************
*   pax_sprite.h
*
*	Tools for manipulating and drawing sprites
******************************************************************************/

#ifndef PAX_SPRITE_H
#define PAX_SPRITE_H

#include <GL/glew.h>

class Sprite {
private:
	int x;
	int y;
	int width;
	int height;

	/* Vertex buffer object */
	GLuint vboID;

public:
	Sprite();
	~Sprite();

	void Initialise(int x, int y, int width, int height);

	void Draw();
};

#endif