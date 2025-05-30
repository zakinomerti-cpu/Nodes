#include "FloatStorage.hpp"

FloatStorage::FloatStorage(): Node(CLASS_NAME)
{
	this->value = std::make_shared<float>(0.0f);

	enableOutPoint(
		Type::FLOAT_T,
		[this]() {
			ImGui::PushItemWidth(100.0f);
			ImGui::PushFont(Font::arial_22);

			ImGui::InputFloat(
				"",
				value.get(),
				0.0f,
				20.0f,
				"%.3f",
				ImGuiInputTextFlags_AllowTabInput
			);

			ImGui::PopFont();
			ImGui::PopItemWidth();
		}
	);
}

std::shared_ptr<float> FloatStorage::getFloat()
{
	return this->value;
}