/******************************************************************************
*   pax_sprite.cpp
*
*	Tools for manipulating and drawing sprites
******************************************************************************/

#include <pax_sprite.h>

Sprite::Sprite()
{
	this->vboID = 0;
}

Sprite::~Sprite()
{
	if (this->vboID != 0) {
		glDeleteBuffers(1, &vboID);
	}
}

void Sprite::Initialise(float x, float y, float width, float height)
{
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;

	if (this->vboID == 0) {
		glGenBuffers(1, &vboID);
	}

	float vertex_data[12];

	// top-right, first triangle
	vertex_data[0] = x + width;
	vertex_data[1] = y + width;
	
	vertex_data[2] = x;
	vertex_data[3] = y + height;

	vertex_data[4] = x;
	vertex_data[5] = y;

	// top-right, second triangle
	vertex_data[6] = x;
	vertex_data[7] = y;

	vertex_data[8] = x + width;
	vertex_data[9] = y;

	vertex_data[10] = x + width;
	vertex_data[11] = y + height;

	glBindBuffer(GL_ARRAY_BUFFER, this->vboID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_data), vertex_data, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Sprite::Draw()
{
	glBindBuffer(GL_ARRAY_BUFFER, this->vboID);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glDisableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
