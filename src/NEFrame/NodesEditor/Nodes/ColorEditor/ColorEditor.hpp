#ifndef _COLOREDITOR_HPP_
#define _COLOREDITOR_HPP_

#include <string>
#include <functional>

#include "NEFrame/NodesEditor/Nodes/Node/Node.hpp"


class ColorEditor: public Node {
public:
	static inline std::string CLASS_NAME = "Color editor";

private:
	const float maxShade = 255.0f;

	intptr red;
	intptr green;
	intptr blue;
	intptr alfa;

	uint redInPointID;
	uint greenInPointID;
	uint blueInPointID;
	uint alfaInPointID;

	v4fptr color;

	float width;
	float textWidth;

public:
	ColorEditor();

	void execute() override;

	void distInt(intptr value, uint inPointID) override;
	std::shared_ptr<Vec4<float>> getVec4() override;

private:
	void drawShadeSliderInPoint(intptr* shade, std::string text);
	void drawShadeTextInPoint(intptr* shade, std::string text);

	float getFloatShade(int shade);
};

#endif // !_COLOREDITOR_HPP_
