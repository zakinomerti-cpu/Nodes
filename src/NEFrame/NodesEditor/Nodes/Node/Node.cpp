#include "Node.hpp"
#include <iostream>


Node::Node(std::string title)
{
	this->nodeID = LAST_NODE_ID++;
	this->outPointID = LAST_NODE_ID++;

	this->title = title;
	this->outType = Type::ZERO_T;

	{
		this->nodeBGCol = IM_COL32(55, 55, 55, 255);
		this->nodeBGHoveredCol = this->nodeBGCol;
		this->nodeBGSelectedCol = IM_COL32(85, 85, 85, 255);

		this->titleBarCol = IM_COL32(4, 0, 120, 255);
		this->titleBarHoveredCol = this->titleBarCol;
		this->titleBarSelectedCol = IM_COL32(20, 37, 156, 255);

		this->nodePinCol = IM_COL32(28, 104, 194, 250);
		this->nodePinHoveredCol = this->nodePinCol;
	}
}

void Node::draw()
{
	pushColorStyle();

	ImNodes::BeginNode(this->nodeID);

	drawTitle();

	for (voidfunc drawFunc: this->nodeDrawPaths)
	{
		drawFunc();
	}

	ImNodes::EndNode();

	popColorStyle();
}

void Node::drawTitle()
{
	ImNodes::BeginNodeTitleBar();

	ImGui::Text(this->title.c_str());

	ImNodes::EndNodeTitleBar();
}

uint Node::getNodeID()
{
	return this->nodeID;
}

std::string Node::getTitle()
{
	return this->title;
}

void Node::setTitle(std::string title)
{
	this->title = title;
}

void Node::setPos(ImVec2 pos)
{
	ImNodes::SetNodeScreenSpacePos(
		getNodeID(), 
		pos
	);
}

void Node::execute()
{
	// Определит дочений класс при необходимости
}

void Node::acceptInt(intptr value, uint inPointID)
{
	distInt(value, inPointID);

	if (!value) openInPoint(inPointID);
	
	else closeInPoint(inPointID);
}

void Node::acceptFloat(floatptr value, uint inPointID)
{
	distFloat(value, inPointID);

	if (!value) openInPoint(inPointID);

	else closeInPoint(inPointID);
}

void Node::acceptVec2(v2fptr vec2, uint inPointID)
{
	distVec2(vec2, inPointID);

	if (!vec2) openInPoint(inPointID);

	else closeInPoint(inPointID);
}

void Node::acceptVec4(v4fptr vec4, uint inPointID)
{
	distVec4(vec4, inPointID);

	if (!vec4) openInPoint(inPointID);

	else closeInPoint(inPointID);
}

void Node::acceptBool(boolptr value, uint inPointID)
{
	distBool(value, inPointID);

	if (!value) openInPoint(inPointID);

	else closeInPoint(inPointID);
}

void Node::acceptString(strptr value, uint inPointID)
{
	distString(value, inPointID);

	if (!value) openInPoint(inPointID);

	else closeInPoint(inPointID);
}

intptr Node::getInt()
{
	// Определит дочений класс при необходимости
	return nullptr;
}

floatptr Node::getFloat()
{
	// Определит дочений класс при необходимости
	return nullptr;
}

v2fptr Node::getVec2()
{
	// Определит дочений класс при необходимости
	return nullptr;
}

v4fptr Node::getVec4()
{
	// Определит дочений класс при необходимости
	return nullptr;
}

boolptr Node::getBool()
{
	// Определит дочений класс при необходимости
	return nullptr;
}

strptr Node::getString()
{
	// Определит дочений класс при необходимости
	return nullptr;
}

void Node::setBGCol(uint red, uint green, uint blue, uint alfa)
{
	this->nodeBGCol = IM_COL32(red, green, blue, alfa);
}

void Node::setBGSelectedCol(uint red, uint green, uint blue, uint alfa)
{
	this->nodeBGSelectedCol = IM_COL32(red, green, blue, alfa);
}

void Node::setBGHoveredCol(uint red, uint green, uint blue, uint alfa)
{
	this->nodeBGHoveredCol = IM_COL32(red, green, blue, alfa);
}

void Node::setTitleBarCol(uint red, uint green, uint blue, uint alfa)
{
	this->titleBarCol = IM_COL32(red, green, blue, alfa);
}

void Node::setTitleBarSelectedCol(uint red, uint green, uint blue, uint alfa)
{
	this->titleBarSelectedCol = IM_COL32(red, green, blue, alfa);
}

void Node::setTitleBarHoveredCol(uint red, uint green, uint blue, uint alfa)
{
	this->titleBarHoveredCol = IM_COL32(red, green, blue, alfa);
}

void Node::setPinCol(uint red, uint green, uint blue, uint alfa)
{
	this->nodePinCol = IM_COL32(red, green, blue, alfa);
}

void Node::setPinHoveredCol(uint red, uint green, uint blue, uint alfa)
{
	this->nodePinHoveredCol = IM_COL32(red, green, blue, alfa);
}

uint Node::getOutPointID()
{
	return this->outPointID;
}

void Node::getInPoinstID(std::list<uint>& inPointIDs)
{
	for (ipdlist::iterator iter = this->inPointDatas.begin(); iter != this->inPointDatas.end(); iter++)
	{
		inPointIDs.emplace_back((*iter)->getPointID());
	}
}

Type Node::getOutType()
{
	return this->outType;
}

bool Node::isAcceptValue(Type type, uint inPointID)
{
	for (ipdlist::iterator iter = this->inPointDatas.begin(); iter != this->inPointDatas.end(); iter++)
	{
		if ((*iter)->getPointID() == inPointID && (*iter)->getType() == type && (*iter)->isFree()) return true;
	}

	return false;
}

bool Node::containInPoint(uint inPointID)
{
	for (ipdlist::iterator iter = this->inPointDatas.begin(); iter != this->inPointDatas.end(); iter++)
	{
		if ((*iter)->getPointID() == inPointID) return true;
	}

	return false;
}

void Node::distInt(intptr value, uint inPointID)
{
	// Определит дочений класс при необходимости
}

void Node::distFloat(floatptr value, uint inPointID)
{
	// Определит дочений класс при необходимости
}

void Node::distVec2(v2fptr vec2, uint inPointID)
{
	// Определит дочений класс при необходимости
}

void Node::distVec4(v4fptr vec4, uint inPointID)
{
	// Определит дочений класс при необходимости
}

void Node::distBool(boolptr value, uint inPointID)
{
	// Определит дочений класс при необходимости
}

void Node::distString(strptr string, uint inPointID)
{
	// Определит дочений класс при необходимости
}

void Node::pushColorStyle()
{
	{ // Цвет заголовка 
		ImNodes::PushColorStyle(
			ImNodesCol_TitleBar,
			this->titleBarCol
		);

		ImNodes::PushColorStyle(
			ImNodesCol_TitleBarHovered,
			this->titleBarHoveredCol
		);

		ImNodes::PushColorStyle(
			ImNodesCol_TitleBarSelected,
			this->titleBarSelectedCol
		);
	}

	{ // Цвет фона нода
		ImNodes::PushColorStyle(
			ImNodesCol_NodeBackground,
			this->nodeBGCol
		);

		ImNodes::PushColorStyle(
			ImNodesCol_NodeBackgroundHovered,
			this->nodeBGHoveredCol
		);

		ImNodes::PushColorStyle(
			ImNodesCol_NodeBackgroundSelected,
			this->nodeBGSelectedCol
		);
	}

	{ // Цвет точек входа / выхода
		ImNodes::PushColorStyle(
			ImNodesCol_Pin,
			this->nodePinCol
		);

		ImNodes::PushColorStyle(
			ImNodesCol_PinHovered,
			this->nodePinHoveredCol
		);
	}
	
	
	
}

void Node::popColorStyle()
{
	{ // Для заголовка
		ImNodes::PopColorStyle();
		ImNodes::PopColorStyle();
		ImNodes::PopColorStyle();
	}
	
	{ // Для фона нода
		ImNodes::PopColorStyle();
		ImNodes::PopColorStyle();
		ImNodes::PopColorStyle();
	}
	
	{ // Для точек входа / выхода
		ImNodes::PopColorStyle();
		ImNodes::PopColorStyle();
	}	
}

uint Node::regInPoint(Type inType, voidfunc wnlf, voidfunc wlf)
{
	std::shared_ptr<InPointData> inPointData = std::make_shared<InPointData>(
		LAST_NODE_ID,
		inType,
		wnlf,
		wlf
	);

	this->inPointDatas.emplace_back(
		inPointData
	);

	addNodeDrawPath(
		[inPointData]() {

			ImNodes::BeginInputAttribute(inPointData->getPointID());

			inPointData->drawPointBody();

			ImNodes::EndInputAttribute();
		}
	);

	return LAST_NODE_ID++;
}

uint Node::regInPoint(Type inType, voidfunc wf)
{
	return regInPoint(inType, wf, wf);
}

void Node::addNodeDrawPath(voidfunc npdf)
{
	this->nodeDrawPaths.emplace_back(npdf);
}

void Node::enableOutPoint(Type outType, voidfunc dpbf)
{
	this->outType = outType;

	addNodeDrawPath(
		[this, dpbf]() {
			ImNodes::BeginOutputAttribute(this->outPointID);

			dpbf();

			ImNodes::EndOutputAttribute();
		}
	);
}

void Node::closeInPoint(uint inPointID)
{
	for (ipdlist::iterator iter = this->inPointDatas.begin(); iter != this->inPointDatas.end(); iter++)
	{
		if ((*iter)->getPointID() == inPointID)
		{
			(*iter)->changeToWLF();

			break;
		}
	}
}

void Node::openInPoint(uint inPointID)
{
	for (ipdlist::iterator iter = this->inPointDatas.begin(); iter != this->inPointDatas.end(); iter++)
	{
		if ((*iter)->getPointID() == inPointID)
		{
			(*iter)->changeToWNLF();

			break;
		}
	}
}
