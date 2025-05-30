#ifndef _NODESEDITOR_HPP_
#define _NODESEDITOR_HPP_

#include <imnodes/imnodes.h>
#include <memory>
#include <functional>

#include "NEFrame/Formating/Vec2.hpp"
#include "ControlPanel/ControlPanel.hpp"
#include "NEFrame/NodesDB/NodesDB.hpp"
#include "NEFrame/Linker/Linker.hpp"
#include "NEFrame/Formating/MouseButtons.hpp"


class NodesEditor {
private:
	ControlPanel* controlPanel;
	NodesDB* nodesDB;
	Linker* linker;

	Vec2<float>* fieldPos;
	std::shared_ptr<Vec2<float>> lastMausePos;

	ImVec2 padding;

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
		ImVec2 pos, 
		ImVec2 size
	);

	void setMoveFieldButton(MouseButton mouseButton);
	void setControlPanelButton(MouseButton mouseButton);

private:
	void pushStyles();
	void popStyles();

	void drawCreationWindow(
		ImVec2 editorPos, 
		ImVec2 editorSize
	);

	void checkMouseEvents();

	void moveField();

	void updateLastMausePos();

	ImVec2 getCorrectCoord(
		ImVec2 winPos, 
		ImVec2 editorPos, 
		ImVec2 editorSize
	);
};

#endif // _NODESEDITOR_HPP_
