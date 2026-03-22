#include "NodesDB.hpp"
#include <iostream>

void NodesDB::doOverNodes(std::function<void(Node*)> func)
{
	for (nodeptr node: this->nodes)
	{
		func(node.get());
	}
}

void NodesDB::doOverLinks(std::function<void(LinkInfo*)> func)
{
	for (liptr linkInfo: this->links)
	{
		func(linkInfo.get());
	}
}

nodeptr NodesDB::getNode(uint nodeID)
{
	try {
		return *this->nodesMap.at(nodeID);
	}

	catch (const std::exception& e)
	{
		return nullptr;
	}
}

liptr NodesDB::getLinkInfo(uint linkID)
{
	try {
		return *this->linkInfoMap.at(linkID);
	}

	catch (const std::exception& e) 
	{
		return nullptr;
	}
}

void NodesDB::delNode(uint nodeID)
{
	try {
		delLinkByNodeID(nodeID);

		this->nodes.erase(
			this->nodesMap.at(nodeID)
		);

		this->nodesMap.erase(nodeID);
	}

	catch (const std::exception& e) {}
}

void NodesDB::delLinkByLinkID(uint linkID)
{
	try {
		lilist::iterator iter = this->linkInfoMap.at(linkID);

		this->graph.erase((*iter)->getNodeOutID());

		this->linkInfoMap.erase(linkID);

		this->links.erase(iter);
	}

	catch (const std::exception& e) {}
}

void NodesDB::delLinkByNodeID(uint nodeID)
{
	try {
		for (l2ilist::iterator iter = this->graph.at(nodeID).begin();
			iter != this->graph.at(nodeID).end();
			iter++
			)
		{
			this->linkInfoMap.erase((**iter)->getLinkID());

			this->links.erase(*iter);
		}

		this->graph.erase(nodeID);
	}

	catch (const std::exception& e) {}
}

nodeptr NodesDB::getSender(uint outPointID)
{
	for (nodeptr node : this->nodes)
	{
		if ((*node).getOutPointID() == outPointID) return node;
	}

	return nullptr;
}

nodeptr NodesDB::getRecipient(uint inPointID)
{
	for (nodeptr node : this->nodes)
	{
		if ((*node).containInPoint(inPointID)) return node;
	}

	return nullptr;
}

void NodesDB::getRecipients(nplist& recipients, uint nodeOutID)
{
	try {
		for (lilist::iterator iter: this->graph.at(nodeOutID))
		{
			recipients.emplace_back(
				std::make_pair(
					*this->nodesMap.at((*iter)->getNodeInID()),
					(*iter)->getInPointID()
				)
			);
		}
	}

	catch (const std::exception& e) {}
}

void NodesDB::addLink(
	uint nodeOutID,
	uint outPointID,
	uint nodeInID,
	uint inPointID
)
{
	this->links.emplace_back(
		std::shared_ptr<LinkInfo>(
			new LinkInfo(
				nodeOutID,
				outPointID,
				nodeInID,
				inPointID,
				this->lastLinkID
			)
		)
	);

	lilist::iterator lastIter = this->links.end();

	lastIter--;
	
	try {
		this->graph.at(nodeOutID).emplace_back(lastIter);
	}

	catch (const std::exception& e) 
	{
		l2ilist liiList;

		liiList.emplace_back(lastIter);

		this->graph.insert(
			std::make_pair(nodeOutID, liiList)
		);
	}

	this->linkInfoMap.insert(
		std::make_pair(this->lastLinkID, lastIter)
	);

	this->lastLinkID++;
}

void NodesDB::addNode(nodeptr node)
{
	this->nodes.emplace_back(node);

	nlist::iterator lastIter = this->nodes.end();

	this->nodesMap.insert(
		std::make_pair(node->getNodeID(), --lastIter)
	);
}
