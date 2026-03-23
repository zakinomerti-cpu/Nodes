//-----------------------------------------------------------------------------
// File: NodesEditor.hpp
// Copyright (c) NIKITOS-V. All rights pirated nahyi
//-----------------------------------------------------------------------------
#ifndef _NODESEDITOR_HPP_
#define _NODESEDITOR_HPP_
#include <functional>



//-----------------------------------------------------------------------------
// Forward declarations
//-----------------------------------------------------------------------------
class Linker;
class NodesDB;
class ControlPanel;
class ImVec2;
class Node;
class LinkInfo;
enum MouseButton;



//-----------------------------------------------------------------------------
// Structure for ControlPanel creation parameters
//-----------------------------------------------------------------------------
struct NODES_EDITOR_PARAMS {
	NodesDB* pNodesDB;
	Linker* pLinker;
};




//-----------------------------------------------------------------------------
// Name: class NodesEditor
// Desc: Operator for (NodesDB, Linker) objects
//-----------------------------------------------------------------------------
class NodesEditor {
private:



	//-------------------------------------------------------------------------
	// Private member variables
	ControlPanel*	controlPanel;
	NodesDB*		nodesDB;
	Linker*			linker;
	ImVec2*			fieldPos;
	ImVec2*			lastMausePos;
	ImVec2*			padding;

	float			miniMapSizeHint;
	MouseButton		moveFieldButtonNumber;
	MouseButton		controlPanelButtonNumber;

	//function pointers
	std::function<void(Node* node)>		drawNodes;
	std::function<void(LinkInfo* node)> drawLinks;



	//-------------------------------------------------------------------------
	// Private methods
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




public:



	//-------------------------------------------------------------------------
	// Public methods	
	NodesEditor(const NODES_EDITOR_PARAMS& params); 	// constructor
	~NodesEditor();
	
	//drawcall
	void draw(ImVec2* pos, ImVec2* size);

	//toolbox
	void setMoveFieldButton(MouseButton mouseButton);
	void setControlPanelButton(MouseButton mouseButton);
};



#endif // _NODESEDITOR_HPP_
