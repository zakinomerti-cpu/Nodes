#include "ColorEditor.hpp"


ColorEditor::ColorEditor() : Node(CLASS_NAME)
{
	this->width = 550.0f;

	this->textWidth = 50.0f;

	this->red = std::make_shared<int>(this->maxShade);
	this->green = std::make_shared<int>(this->maxShade);
	this->blue = std::make_shared<int>(this->maxShade);
	this->alfa = std::make_shared<int>(this->maxShade);

	this->redInPointID = regInPoint(
		Type::INT_T,
		[this]() {
			this->drawShadeSliderInPoint(&this->red, "red");
		},
		[this]() {
			this->drawShadeTextInPoint(&this->red, "red");
		}
	);

	this->greenInPointID = regInPoint(
		Type::INT_T,
		[this]() {
			this->drawShadeSliderInPoint(&this->green, "green");
		},
		[this]() {
			this->drawShadeTextInPoint(&this->green, "green");
		}
	);

	this->blueInPointID = regInPoint(
		Type::INT_T,
		[this]() {
			this->drawShadeSliderInPoint(&this->blue, "blue");
		},
		[this]() {
			this->drawShadeTextInPoint(&this->blue, "blue");
		}
	);

	this->alfaInPointID = regInPoint(
		Type::INT_T,
		[this]() {
			this->drawShadeSliderInPoint(&this->alfa, "alfa");
		},
		[this]() {
			this->drawShadeTextInPoint(&this->alfa, "alfa");
		}
	);

	enableOutPoint(
		Type::VEC4_T,
		[]() {
			ImGui::Text("");
		}
	);

	this->color = std::make_shared<Vec4<float>>(
		getFloatShade(*this->red),
		getFloatShade(*this->green),
		getFloatShade(*this->blue),
		getFloatShade(*this->alfa)
	);

	setTitleBarCol(150, 0, 0, 255);
	setTitleBarHoveredCol(150, 0, 0, 255);
	setTitleBarSelectedCol(190, 0, 0, 255);

	setPinCol(190, 0, 0, 255);
	setPinHoveredCol(255, 0, 0, 255);
}

void ColorEditor::execute()
{
	this->color->setX(
		getFloatShade(*this->red)
	);

	this->color->setY(
		getFloatShade(*this->green)
	);

	this->color->setW(
		getFloatShade(*this->blue)
	);

	this->color->setZ(
		getFloatShade(*this->alfa)
	);
}

void ColorEditor::distInt(intptr value, uint inPointID)
{
	if (inPointID == this->redInPointID)
	{
		if (!value) this->red = std::make_shared<int>(*this->red);

		else this->red = value;
	}

	else if (inPointID == this->greenInPointID)
	{
		if (!value) this->green = std::make_shared<int>(*this->green);

		else this->green = value;
	}

	else if (inPointID == this->blueInPointID)
	{
		if (!value) this->blue = std::make_shared<int>(*this->blue);

		else this->blue = value;
	}

	else if (inPointID == this->alfaInPointID)
	{
		if (!value) this->alfa = std::make_shared<int>(*this->alfa);

		else this->alfa = value;
	}
}

std::shared_ptr<Vec4<float>> ColorEditor::getVec4()
{
	return this->color;
}

void ColorEditor::drawShadeSliderInPoint(intptr* shade, std::string text)
{
	ImGui::Text(text.c_str());

	ImGui::SameLine(this->textWidth);

	ImGui::Text(":");

	ImGui::SameLine();

	ImGui::SetNextItemWidth(this->width - this->textWidth);
	ImGui::SliderInt(
		"",
		shade->get(),
		0,
		this->maxShade
	);
}

void ColorEditor::drawShadeTextInPoint(intptr* shade, std::string text)
{
	ImGui::Text(text.c_str());

	ImGui::SameLine(this->textWidth);

	ImGui::Text(":");

	ImGui::SameLine();

	ImGui::Text((std::to_string(**shade)).c_str());
}

float ColorEditor::getFloatShade(int shade)
{
	return shade / this->maxShade;
}
