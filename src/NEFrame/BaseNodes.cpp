#include "BaseNodes.hpp"

#include "NEFrame/NodesEditor/Nodes/FPSNode/FPSNode.hpp"
#include "NEFrame/NodesEditor/Nodes/Node/NodeBuilder.hpp"
#include "NEFrame/NodesEditor/Nodes/IntStorage/IntStorage.hpp"
#include "NEFrame/NodesEditor/Nodes/FloatStorage/FloatStorage.hpp"
#include "NEFrame/NodesEditor/Nodes/ColorEditor/ColorEditor.hpp"
#include "NEFrame/NodesEditor/Nodes/MultStrEditor/MultStrEditor.hpp"
#include "NEFrame/NodesEditor/Nodes/ShaderVisualizer/ShaderVisualizer.hpp"

#include "NEFrame/NodesEditor/ControlPanel/ControlPanel.hpp"

void FillControlPanel(ControlPanel* pControlPanel) {



    // Define node builder parameters
    const NODE_BUILDER_PARAMS aNodeParams[] =
    {
        { []() { return std::make_shared<IntStorage>();  },
            IntStorage::CLASS_NAME.c_str()},
        { []() { return std::make_shared<FloatStorage>(); },
            FloatStorage::CLASS_NAME.c_str() },
        { []() { return std::make_shared<ColorEditor>(); },
            ColorEditor::CLASS_NAME.c_str()  },
        { []() { return std::make_shared<FPSNode>(); },
            FPSNode::CLASS_NAME.c_str()      },
        {[]() { return std::make_shared<ShaderVisualizer>();  },
            ShaderVisualizer::CLASS_NAME.c_str() },
    };



    // Register all node types
    const int dwNumNodes = sizeof(aNodeParams) / sizeof(aNodeParams[0]);
    for (int i = 0; i < dwNumNodes; i++) {
        pControlPanel->addNodeBuilder(
            NodeBuilder(aNodeParams[i].pfnCreator, aNodeParams[i].pszClassName)
        );
    }
}