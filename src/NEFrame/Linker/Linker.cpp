#include "Linker.hpp"

Linker::Linker(NodesDB* nodesDD)
{
	this->nodesDB = nodesDD;
	
	fillLinkNodesFuncsList();
	fillUnlinkNodesFuncsList();
}

Linker::~Linker()
{
	this->linkNodesFuncs.clear();
	this->unlinkNodesFuncs.clear();
}

void Linker::checkNewLinks()
{
	int outPointID, inPointID;

	if (!ImNodes::IsLinkCreated(&outPointID, &inPointID)) return;
	
	nodeptr nodeOut = this->nodesDB->getSender(outPointID);
	nodeptr nodeIn = this->nodesDB->getRecipient(inPointID);

	if (nodeOut->getOutType() == Type::ZERO_T) return;

	if (nodeOut->getNodeID() == nodeIn->getNodeID()) return;

	if (!nodeIn->isAcceptValue(nodeOut->getOutType(), inPointID)) return;

	if (!this->linkNodesFuncs.at(nodeOut->getOutType())(nodeOut, nodeIn, inPointID)) return;

	this->nodesDB->addLink(
		nodeOut->getNodeID(),
		outPointID,
		nodeIn->getNodeID(),
		inPointID
	);
}

void Linker::delSelectedNodes()
{
	const int numSelectedNodes = ImNodes::NumSelectedNodes();

	if (numSelectedNodes > 0)
	{
		nplist recipients;

		std::vector<int> selectedNodes;
		selectedNodes.resize(numSelectedNodes);

		ImNodes::GetSelectedNodes(selectedNodes.data());

		for (int nodeID : selectedNodes)
		{
			this->nodesDB->getRecipients(recipients, nodeID);

			for (nplist::iterator iter = recipients.begin(); iter != recipients.end(); iter++)
			{
				nodeptr nodeOut = this->nodesDB->getNode(nodeID);

				if (!nodeOut) continue;

				this->unlinkNodesFuncs.at(
					nodeOut->getOutType() 
				)(
					iter->first, // Умный указатель на нод
					iter->second // ID точки входа
				);
			}

			this->nodesDB->delNode(nodeID);

			recipients.clear();
		}

		selectedNodes.clear();
	}
}

void Linker::delSelectedLinks()
{
	const int numSelectedLinks = ImNodes::NumSelectedLinks();

	if (numSelectedLinks > 0)
	{
		std::vector<int> selectedLinks;
		selectedLinks.resize(numSelectedLinks);

		ImNodes::GetSelectedLinks(selectedLinks.data());

		for (int linkID : selectedLinks)
		{
			liptr linkInfo = this->nodesDB->getLinkInfo(linkID);

			if (!linkInfo) continue;

			nodeptr nodeOut = this->nodesDB->getNode(linkInfo->getNodeOutID());
			nodeptr nodeIn = this->nodesDB->getNode(linkInfo->getNodeInID());

			if (!nodeOut || !nodeIn) continue;
			
			this->unlinkNodesFuncs.at(nodeOut->getOutType())(nodeIn, linkInfo->getInPointID());

			this->nodesDB->delLinkByLinkID(linkID);
		}
	}
}

void Linker::fillLinkNodesFuncsList()
{
	this->linkNodesFuncs.insert(std::make_pair(
		Type::INT_T,
		[](nodeptr nodeOut, nodeptr nodeIn, uint inPointID)
		{
			if (!nodeOut->getInt()) return false;

			nodeIn->acceptInt(
				nodeOut->getInt(),
				inPointID
			);

			return true;
		}
	));

	this->linkNodesFuncs.insert(std::make_pair(
		Type::FLOAT_T,
		[](nodeptr nodeOut, nodeptr nodeIn, uint inPointID)
		{
			if (!nodeOut->getFloat()) return false;

			nodeIn->acceptFloat(
				nodeOut->getFloat(),
				inPointID
			);

			return true;
		}
	));

	this->linkNodesFuncs.insert(std::make_pair(
		Type::STRING_T,
		[](nodeptr nodeOut, nodeptr nodeIn, uint inPointID)
		{
			if (!nodeOut->getString()) return false;

			nodeIn->acceptString(
				nodeOut->getString(),
				inPointID
			);

			return true;
		}
	));
}

void Linker::fillUnlinkNodesFuncsList()
{
	this->unlinkNodesFuncs.insert(std::make_pair(
		Type::INT_T,
		[](nodeptr nodeIn, uint inPointID) {
			nodeIn->acceptInt(nullptr, inPointID);
		}
	));

	this->unlinkNodesFuncs.insert(std::make_pair(
		Type::FLOAT_T,
		[](nodeptr nodeIn, uint inPointID) {
			nodeIn->acceptFloat(nullptr, inPointID);
		}
	));

	this->unlinkNodesFuncs.insert(std::make_pair(
		Type::STRING_T,
		[](nodeptr nodeIn, uint inPointID) {
			nodeIn->acceptString(nullptr, inPointID);
		}
	));
}
