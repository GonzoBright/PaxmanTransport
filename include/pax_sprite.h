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
	float x;
	float y;
	float width;
	float height;

	/* Vertex buffer object */
	GLuint vboID;

public:
	Sprite();
	~Sprite();

	void Initialise(float x, float y, float width, float height);

	void Draw();
};

#endif