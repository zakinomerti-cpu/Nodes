#include "NodeBuilder.hpp"

NodeBuilder::NodeBuilder(nbf buildNodeFunc, std::string nodeName)
{
	this->defaultSpawnPos = ImVec2(0.0f, 0.0f);

	this->buildNode = buildNodeFunc;
	this->nodeName = nodeName;
}

std::shared_ptr<Node> NodeBuilder::build()
{
	std::shared_ptr<Node> node = this->buildNode();
	node->setPos(this->spawnPos);

	clearSpawnPos();

	return node;
}

NodeBuilder* NodeBuilder::setPos(ImVec2 pos)
{
	this->spawnPos = pos;

	return this;
}

std::string NodeBuilder::getNodeName()
{
	return this->nodeName;
}

void NodeBuilder::clearSpawnPos()
{
	this->spawnPos = this->defaultSpawnPos;
}
