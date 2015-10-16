#ifndef PAX_IMAGELOADER_H
#define PAX_IMAGELOADER_H

#include <pax_gltexture.h>

class ImageLoader {
public:
	static GLTexture LoadPNG(char* file_path);
};

#endif