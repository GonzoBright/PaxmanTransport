#ifndef PAX_IOMANAGER_H
#define PAX_IOMANAGER_H

#include <vector>

class IOManager {
public:
	static bool ReadFileToBuffer(char* file_path, std::vector<unsigned char> &buffer);
};

#endif