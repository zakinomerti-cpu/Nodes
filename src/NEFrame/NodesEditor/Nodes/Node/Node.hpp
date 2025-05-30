#ifndef _NODE_
#define _NODE_

#include <unordered_map>
#include <memory>
#include <string>
#include <imnodes/imnodes.h>

#include "NEFrame/Formating/Vec4.hpp"
#include "NEFrame/Formating/InPointData.hpp"
#include "NEFrame/Formating/Fonts.hpp"

typedef unsigned int uint;

typedef std::list<std::shared_ptr<InPointData>> ipdlist;

typedef std::list<voidfunc> npdfuncs;

typedef std::shared_ptr<int> intptr;
typedef std::shared_ptr<float> floatptr;
typedef std::shared_ptr<Vec2<float>> v2fptr;
typedef std::shared_ptr<Vec4<float>> v4fptr;
typedef std::shared_ptr<bool> boolptr;
typedef std::shared_ptr<std::string> strptr;

class Node {
private:
	static inline uint LAST_NODE_ID = 0;

	uint nodeID;
	uint outPointID;

	ipdlist inPointDatas;

	Type outType;
	std::string title;

	npdfuncs nodeDrawPaths;

	// Цвета
	uint titleBarCol;
	uint titleBarSelectedCol;
	uint titleBarHoveredCol;

	uint nodeBGCol;
	uint nodeBGSelectedCol;
	uint nodeBGHoveredCol;

	uint nodePinCol;
	uint nodePinHoveredCol;
	
public:
	Node(std::string title);

	void draw();

	uint getNodeID();
	uint getOutPointID();
	void getInPoinstID(std::list<uint>& inPointIDs);

	std::string getTitle();
	Type getOutType();

	void setTitle(std::string title);
	void setPos(ImVec2 pos);

	bool isAcceptValue(Type type, uint inPointID);
	bool containInPoint(uint inPointID);

	void acceptInt(intptr value, uint inPointID);
	void acceptFloat(floatptr value, uint inPointID);
	void acceptVec2(v2fptr vec2, uint inPointID);
	void acceptVec4(v4fptr vec4, uint inPointID);
	void acceptBool(boolptr value, uint inPointID);
	void acceptString(strptr value, uint inPointID);

	// Определять при необходимости
	void virtual execute();

	// Определять при необходимости
	virtual intptr getInt();
	virtual floatptr getFloat();
	virtual v2fptr getVec2();
	virtual v4fptr getVec4();
	virtual boolptr getBool();
	virtual strptr getString();

protected:
	uint regInPoint(Type inType, voidfunc wnlf, voidfunc wlf);
	uint regInPoint(Type inType, voidfunc wf);

	void addNodeDrawPath(voidfunc npdf);

	void enableOutPoint(Type outType, voidfunc dpbf);

	// Определять при необходимости
	virtual void distInt(intptr value, uint inPointID);
	virtual void distFloat(floatptr value, uint inPointID);
	virtual void distVec2(v2fptr vec2, uint inPointID);
	virtual void distVec4(v4fptr vec4, uint inPointID);
	virtual void distBool(boolptr value, uint inPointID);
	virtual void distString(strptr string, uint inPointID);

	void setBGCol(uint red, uint green, uint blue, uint alfa);
	void setBGSelectedCol(uint red, uint green, uint blue, uint alfa);
	void setBGHoveredCol(uint red, uint green, uint blue, uint alfa);

	void setTitleBarCol(uint red, uint green, uint blue, uint alfa);
	void setTitleBarSelectedCol(uint red, uint green, uint blue, uint alfa);
	void setTitleBarHoveredCol(uint red, uint green, uint blue, uint alfa);

	void setPinCol(uint red, uint green, uint blue, uint alfa);
	void setPinHoveredCol(uint red, uint green, uint blue, uint alfa);

private:
	void pushColorStyle();
	void popColorStyle();

	void drawTitle();

	void closeInPoint(uint inPoint);
	void openInPoint(uint inPoint);
};

#endif // !_NODE_