#include "MultStrEditor.hpp"

MultStrEditor::MultStrEditor(FileHandler* fileHandler, std::string filePath): Node(CLASS_NAME)
{
	this->fileHandler = fileHandler;
	this->filePath = filePath;

	this->multiSting = std::make_shared<std::string>("");

	this->textFieldWidth = 800.0f;
	this->textFieldHeight = 500.0f;


	addNodeDrawPath(
		[this]() {
			if (ImGui::Button("Save", ImVec2(this->textFieldWidth, 25.0f)))
			{
				this->fileHandler->writeFile(
					this->filePath,
					*this->multiSting
				);
			}
		}
	);

	addNodeDrawPath(
		[this]()
		{
			ImGui::PushFont(Font::calibri_24);

			ImGui::InputTextMultiline(
				"##",
				this->multiSting.get(),
				ImVec2(this->textFieldWidth, this->textFieldHeight),
				ImGuiInputTextFlags_AllowTabInput
			);

			ImGui::PopFont();
		}
	);

	setTitleBarCol(165, 60, 0, 255);
	setTitleBarHoveredCol(165, 60, 0, 255);
	setTitleBarSelectedCol(205, 100, 40, 255);
}

strptr MultStrEditor::getString()
{
	return this->multiSting;
}
