#ifndef _FILE_HANDLER_
#define _FILE_HANDLER_

#include "string"
#include <fstream>
#include <sstream>


class FileHandler {
public:
	std::string readFile(std::string path);
	void writeFile(std::string path, std::string text);
};

#endif // _FILE_HANDLER_

