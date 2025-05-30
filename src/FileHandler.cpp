#include "FileHandler.hpp"

std::string FileHandler::readFile(std::string path)
{
	std::string line;
	std::string outputstring;

	std::ifstream file(path.c_str());

	if (file.is_open()) {
		while (std::getline(file, line)) {
			outputstring += line + '\n';
		}
	}

	file.close();
	return outputstring;
}

void FileHandler::writeFile(std::string path, std::string text)
{
	std::ofstream out;
	out.open(path);

	std::stringstream stringStream(text);
	std::string line;

	if (out.is_open())
	{
		while (std::getline(stringStream, line, '\n'))
		{
			out << line << '\n';
		}
	}
	out.close();
}
