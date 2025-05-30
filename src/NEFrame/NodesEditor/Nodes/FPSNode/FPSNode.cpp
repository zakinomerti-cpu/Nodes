#include "FPSNode.hpp"

FPSNode::FPSNode(): Node(CLASS_NAME)
{
	addNodeDrawPath(
		[]()
		{
			ImGui::Text("FPS: %.1f", ImGui::GetIO().Framerate);
		}
	);
}
