#include <pax_iomanager.h>

#include <fstream>

bool IOManager::ReadFileToBuffer(char * file_path, std::vector<unsigned char>& buffer)
{
	std::ifstream file(file_path, std::ios::binary);
	if (file.fail()) {
		perror(file_path);
		return false;
	}

	// seek to end of file
	// 0 bytes FROM the end of the file
	file.seekg(0, std::ios::end);

	// Get file size
	int file_size = file.tellg();
	// return to the beginning of the file
	file.seekg(0, std::ios::beg);

	// Disregard any headers placed beforehand
	file_size -= file.tellg();

	// Resize buffer
	buffer.resize(file_size);

	// Pointer to a c_str
	file.read((char*)&(buffer[0]), file_size);
	file.close();

	return true;
}
