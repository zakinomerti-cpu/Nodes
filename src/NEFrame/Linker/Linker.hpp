#ifndef _LINKER_
#define _LINKER_

#include <imnodes/imnodes.h>
#include <functional>
#include <unordered_map>

#include "NeFrame/NodesDB/NodesDB.hpp"

class Linker {
private:
	NodesDB* nodesDB;

	std::unordered_map <Type, std::function<bool(nodeptr nodeOut, nodeptr nodeIn, uint inPointID) >> linkNodesFuncs;
	std::unordered_map <Type, std::function<void(nodeptr nodeOut, uint inPointID) >> unlinkNodesFuncs;

public:
	Linker(NodesDB* nodesDB);
	~Linker();

	void checkNewLinks();
	void delSelectedNodes();
	void delSelectedLinks();

private:
	void fillLinkNodesFuncsList();
	void fillUnlinkNodesFuncsList();
};

#endif // _LINKER_

