#ifndef _NODE_BUILDER_
#define _NODE_BUILDER_

#include "Node.hpp"
#include "memory"

typedef std::function<std::shared_ptr<Node>()> nbf;

class NodeBuilder {
private:
	ImVec2 defaultSpawnPos;
	ImVec2 spawnPos;

	std::string nodeName;
	
	nbf buildNode;

public:
	NodeBuilder(nbf buildNodeFunc, std::string nodeName);

	std::shared_ptr<Node> build();

	NodeBuilder* setPos(ImVec2 pos);

	std::string getNodeName();

private:
	void clearSpawnPos();
};

#endif // _NODE_BUILDER_
