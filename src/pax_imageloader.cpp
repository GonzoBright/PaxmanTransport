#include <pax_imageloader.h>

#include <pax_iomanager.h>
#include <pax_error.h>
#include <picoPNG.h>

GLTexture ImageLoader::LoadPNG(char * file_path)
{
	GLTexture texture = {};

	// Output
	std::vector<unsigned char> out;
	std::vector<unsigned char> in;

	unsigned long width, height;

	if (IOManager::ReadFileToBuffer(file_path, in) == false) {
		// error occurred whilst reading the input file
		FatalError("ImageLoader: Failed to load PNG to buffer");
	}

	int error_code = decodePNG(out, width, height, &(in[0]), in.size());
	if (error_code != 0) {
		// 0 = no error
		FatalError("ImageLoader: PNG decoder failed with error: " + error_code);
	}

	// Generate texture
	glGenTextures(1, &(texture.id));

	// Bind texture
	glBindTexture(GL_TEXTURE_2D, texture.id);

	// Fill with data
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &(out[0]));

	// Specify a few parameters for the texture itself
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	glGenerateMipmap(GL_TEXTURE_2D);

	// Make sure to un-bind the texture after use
	glBindTexture(GL_TEXTURE_2D, 0);

	texture.width = width;
	texture.height = height;

	return texture;
}
