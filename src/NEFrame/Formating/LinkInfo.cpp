#include "LinkInfo.hpp"

LinkInfo::LinkInfo(
	unsigned int nodeOutID,
	unsigned int outPointID,
	unsigned int nodeInID,
	unsigned int inPointID,
	unsigned int linkID
)
{
	this->nodeOutID = nodeOutID;
	this->outPointID = outPointID;
	this->nodeInID = nodeInID;
	this->inPointID = inPointID;
	this->linkID = linkID;
}

unsigned int LinkInfo::getInPointID()
{
	return this->inPointID;
}

unsigned int LinkInfo::getNodeInID()
{
	return this->nodeInID;
}

unsigned int LinkInfo::getOutPointID()
{
	return this->outPointID;
}

unsigned int LinkInfo::getNodeOutID()
{
	return this->nodeOutID;
}

unsigned int LinkInfo::getLinkID()
{
	return this->linkID;
}
