#ifndef _FPS_NODE_
#define _FPS_NODE_

#include <string>

#include "NEFrame/NodesEditor\Nodes\Node\Node.hpp"


class FPSNode: public Node {
public:
	static inline std::string CLASS_NAME = "FPS node";

public:
	FPSNode();
};

#endif // _FPS_NODE_


