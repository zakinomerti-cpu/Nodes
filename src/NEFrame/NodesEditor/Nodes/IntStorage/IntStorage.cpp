#include "IntStorage.hpp"

IntStorage::IntStorage() : Node(CLASS_NAME)
{
	this->value = std::make_shared<int>(0);
	
	enableOutPoint(
		Type::INT_T,
		[this]()
		{
			ImGui::PushItemWidth(100.0f);
			ImGui::PushFont(Font::arial_22);

			ImGui::InputInt(
				"",
				this->value.get(),
				0,
				20,
				ImGuiInputTextFlags_AllowTabInput
			);

			ImGui::PopFont();
			ImGui::PopItemWidth();
		}
	);
}

intptr IntStorage::getInt()
{
	return this->value;
}
