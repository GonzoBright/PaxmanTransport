/******************************************************************************
*   pax_sprite.cpp
*
*	Tools for manipulating and drawing sprites
******************************************************************************/

#include <pax_sprite.h>
#include <pax_vertex.h>

#include <cstdlib>

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

	Vertex vertex_data[6];

	// top-right, first triangle
	vertex_data[0].position.x = x + width;
	vertex_data[0].position.y = y + width;
	
	vertex_data[1].position.x = x;
	vertex_data[1].position.y = y + height;

	vertex_data[2].position.x = x;
	vertex_data[2].position.y = y;

	// top-right, second triangle
	vertex_data[3].position.x = x;
	vertex_data[3].position.y = y;

	vertex_data[4].position.x = x + width;
	vertex_data[4].position.y = y;

	vertex_data[5].position.x = x + width;
	vertex_data[5].position.y = y + height;

	for (int i = 0; i < 6; i++) {
		// Magenta
		vertex_data[i].colour.r = 255;
		vertex_data[i].colour.g = 0;
		vertex_data[i].colour.b = 255;
		vertex_data[i].colour.a = 255;
	}

	vertex_data[1].colour.r = 0;
	vertex_data[1].colour.g = 0;
	vertex_data[1].colour.b = 255;
	vertex_data[1].colour.a = 255;

	vertex_data[4].colour.r = 0;
	vertex_data[4].colour.g = 255;
	vertex_data[4].colour.b = 0;
	vertex_data[4].colour.a = 255;

	glBindBuffer(GL_ARRAY_BUFFER, this->vboID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_data), vertex_data, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Sprite::Draw()
{
	glBindBuffer(GL_ARRAY_BUFFER, this->vboID);

	glEnableVertexAttribArray(0);

	// Position attribute pointer
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
	// Colour attribute pointer, index 1, four bytes
	glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, colour));

	glDrawArrays(GL_TRIANGLES, 0, 6);

	glDisableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
