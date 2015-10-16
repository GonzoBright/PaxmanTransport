#ifndef PAX_VERTEX_H
#define PAX_VERTEX_H

struct Position {
	float x;
	float y;
};

struct Colour {
	unsigned char r;
	unsigned char g;
	unsigned char b;
	unsigned char a;
};

struct Vertex {
	Position position;

	Colour colour;
};

#endif