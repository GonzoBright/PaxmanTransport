#ifndef PAX_GLTEXTURE_H
#define PAX_GLTEXTURE_H

#include <GL/glew.h>

struct GLTexture {
	GLuint id;
	int width;
	int height;
};

#endif