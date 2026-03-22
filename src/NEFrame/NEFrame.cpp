//-----------------------------------------------------------------------------
// File: NEFrame.cpp
// Copyright (c) NIKITOS-V. All rights pirated nahyi
//-----------------------------------------------------------------------------
#include <functional>
#include <string>

#include "NEFrame.hpp"
#include "NEFrame/NodesDB/NodesDB.hpp"
#include "NEFrame/NodesEditor/Nodes/Node/Node.hpp"
#include "NodesEditor/NodesEditor.hpp"
#include "NEFrame/NodesEditor/ControlPanel/ControlPanel.hpp"
#include "NEFrame/Linker/Linker.hpp"
#include "NEFrame/NodesEditor/Nodes/Node/NodeBuilder.hpp"
#include "NEFrame/NodesEditor/Nodes/IntStorage/IntStorage.hpp"
#include "NEFrame/NodesEditor/Nodes/FloatStorage/FloatStorage.hpp"
#include "NEFrame/NodesEditor/Nodes/ColorEditor/ColorEditor.hpp"
#include "NEFrame/NodesEditor/Nodes/MultStrEditor/MultStrEditor.hpp"
#include "NEFrame/NodesEditor/Nodes/FPSNode/FPSNode.hpp"
#include "FileHandler.hpp"



//-----------------------------------------------------------------------------
// Structure for node builder creation parameters
//-----------------------------------------------------------------------------
struct NODE_BUILDER_PARAMS {
    std::function<std::shared_ptr<Node>()> pfnCreator;
    const char* pszClassName;
};



//-----------------------------------------------------------------------------
// Name: NEFrame()
// Desc: Constructor for the main frame class
//-----------------------------------------------------------------------------
NEFrame::NEFrame() {
    


    // Initialize core components
    m_pNodesDB = new NodesDB();
    m_pLinker = new Linker(m_pNodesDB);
    m_pFileHandler = new FileHandler();



    // Setup ControlPanel parameters
    CONTROL_PANEL_PARAMS cpParams;
    cpParams.vInitialSize = ImVec2(250, 120);
    cpParams.pNodesDB = m_pNodesDB;
    cpParams.pLinker = m_pLinker;
    m_pControlPanel = new ControlPanel(cpParams);



    // Setup NodesEditor parameters
    NODES_EDITOR_PARAMS neParams;
    neParams.pNodesDB = m_pNodesDB;
    neParams.pLinker = m_pLinker;
    neParams.pControlPanel = m_pControlPanel;
    m_pNodesEditor = new NodesEditor(neParams);



    // Fill control panel with node builders
    fillControlPanel();



    // Initialize shader path
    this->m_pShaderPath = _strdup("shaderTXT.txt");

}

NEFrame::~NEFrame() {

    

    //cleanup
    delete m_pNodesDB;
    delete m_pLinker;
    delete m_pControlPanel;
    delete m_pNodesEditor;
    delete m_pFileHandler;
    delete m_pShaderPath;
}

void NEFrame::fillControlPanel()
{



    // Define node builder parameters
    const NODE_BUILDER_PARAMS aNodeParams[] =
    {
        { []() { return std::make_shared<IntStorage>();  },   
            IntStorage::CLASS_NAME.c_str()},
        { []() { return std::make_shared<FloatStorage>(); },   
            FloatStorage::CLASS_NAME.c_str() },
        { []() { return std::make_shared<ColorEditor>(); },    
            ColorEditor::CLASS_NAME.c_str()  },
        { [this]() { return std::make_shared<MultStrEditor>
            (m_pFileHandler, "shaderTXT.txt"); }, 
            MultStrEditor::CLASS_NAME.c_str() },
        { []() { return std::make_shared<FPSNode>(); },        
            FPSNode::CLASS_NAME.c_str()      }
    };



    // Register all node types
    const int dwNumNodes = sizeof(aNodeParams) / sizeof(aNodeParams[0]);
    for (int i = 0; i < dwNumNodes; i++) {
        m_pControlPanel->addNodeBuilder(
            NodeBuilder(aNodeParams[i].pfnCreator, aNodeParams[i].pszClassName)
        );
    }
}



//-----------------------------------------------------------------------------
// Name: Draw()
// Desc: Renders the main frame and all its child components
//-----------------------------------------------------------------------------
void NEFrame::draw(int width, int height) {
    ImVec2 LeftUp = ImVec2(0, 0);
    ImVec2 RightDown = ImVec2(width, height);
    this->m_pNodesEditor->draw(&LeftUp, &RightDown);
}
