#ifndef _NODESEDITOR_HPP_
#define _NODESEDITOR_HPP_

#include <Windows.h>
#include <imnodes/imnodes.h>
#include <imgui/imgui.h>
#include <functional>

#include "NEFrame/Formating/MouseButtons.hpp"
#include "NEFrame/Linker/Linker.hpp"
#include "ControlPanel/ControlPanel.hpp"
#include "NEFrame/NodesDB/NodesDB.hpp"

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
