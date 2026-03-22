#ifndef _CONTROL_PANEL_
#define _CONTROL_PANEL_

# include <imgui/imgui.h>
#include "NeFrame/NodesDB/NodesDB.hpp"
#include "NeFrame/NodesEditor/Nodes/Node/NodeBuilder.hpp"
#include "NeFrame/Linker/Linker.hpp"

typedef std::list<NodeBuilder> nblist;

//-----------------------------------------------------------------------------
// Structure for ControlPanel creation parameters
//-----------------------------------------------------------------------------
struct CONTROL_PANEL_PARAMS
{
	ImVec2      vInitialSize;
	NodesDB* pNodesDB;
	Linker* pLinker;
};

class ControlPanel {
private:
	nblist nodeBuilders;

	NodesDB* nodesDB;
	Linker* linker;

	ImVec2 size;
	ImVec2 padding;

	float buttonSizeHint;

	bool active;
	
	std::function<void(ImVec2)> drawCurentMenu;
	std::function<void(ImVec2)> drawMainMenu;
	std::function<void(ImVec2)> drawCreationMenu;

public:
	ControlPanel(
		ImVec2 size, 
		NodesDB* nodesDB, 
		Linker* linker
	);

	ControlPanel(const CONTROL_PANEL_PARAMS& params);
	~ControlPanel();

	void draw(ImVec2 pos);

	ImVec2 getSize();
	void setSize(ImVec2 size);

	void activate();
	void deactivate();
	bool isActive();

	void addNodeBuilder(NodeBuilder nodeBuilder);

private:
	void createMainMenu();
	void createCreationMenu();

	ImVec2 getButtonSize();

	void changeToMainMenu();
	void changeToCreationMenu();

	void checkFocused();
};

#endif // _CONTROL_PANEL_

