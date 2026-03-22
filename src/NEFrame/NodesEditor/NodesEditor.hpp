#ifndef _NODESEDITOR_HPP_
#define _NODESEDITOR_HPP_

#include <functional>
#include "NEFrame/Formating/MouseButtons.hpp"
#include "NEFrame/NodesDB/NodesDB.hpp"

class Linker;
class NodesDB;
class ControlPanel;
class ImVec2;
class Node;
class LinkInfo;

struct NODES_EDITOR_PARAMS {
	ControlPanel* pControlPanel;
	NodesDB* pNodesDB;
	Linker* pLinker;
};


class NodesEditor {
private:
	ControlPanel* controlPanel;
	NodesDB* nodesDB;
	Linker* linker;

	ImVec2* fieldPos;
	ImVec2* lastMausePos;
	ImVec2* padding;

	float miniMapSizeHint;

	MouseButton moveFieldButtonNumber;
	MouseButton controlPanelButtonNumber;

	std::function<void(Node* node)> drawNodes;
	std::function<void(LinkInfo* node)> drawLinks;

public:
	NodesEditor(
		NodesDB* nodesDB, 
		Linker* linker, 
		ControlPanel* controlPanel
	);
	NodesEditor(const NODES_EDITOR_PARAMS& params);
	~NodesEditor();

	void draw(
		ImVec2* pos,
		ImVec2* size
	);

	void setMoveFieldButton(MouseButton mouseButton);
	void setControlPanelButton(MouseButton mouseButton);

private:
	void pushStyles();
	void popStyles();

	void drawCreationWindow(
		ImVec2* editorPos,
		ImVec2* editorSize
	);

	void checkMouseEvents();
	void moveField();
	void updateLastMausePos();

	ImVec2* getCorrectCoord(
		ImVec2* winPos,
		ImVec2* editorPos,
		ImVec2* editorSize
	);
};

#endif // _NODESEDITOR_HPP_
