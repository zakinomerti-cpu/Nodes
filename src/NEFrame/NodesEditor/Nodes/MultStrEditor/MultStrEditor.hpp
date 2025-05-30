#ifndef _MULTILINE_STRING_EDITOR_
#define _MULTILINE_STRING_EDITOR_

#include <imgui\imgui_stdlib.h>

#include "NEFrame/NodesEditor/Nodes/Node/Node.hpp"
#include "FileHandler.hpp"


class MultStrEditor: public Node {
public:
	static inline std::string CLASS_NAME = "Shader editor";

private:
	FileHandler* fileHandler;

	std::string filePath;

	strptr multiSting;

	float textFieldWidth;
	float textFieldHeight;

public:
	MultStrEditor(FileHandler* fileHandler, std::string filePath);

	strptr getString() override;
};

#endif // _MULTILINE_STRING_EDITOR_

