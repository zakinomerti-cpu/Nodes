//-----------------------------------------------------------------------------
// File: NEFrame.cpp
// Copyright (c) NIKITOS-V. All rights pirated nahyi
//-----------------------------------------------------------------------------

#include "NEFrame.hpp"
#include "NEFrame/NodesEditor/NodesEditor.hpp"
#include "NEFrame/NodesEditor/ControlPanel/ControlPanel.hpp"
#include "FileHandler.hpp"
#include "BaseNodes.hpp"



//-----------------------------------------------------------------------------
// Name: NEFrame()
// Desc: Constructor for the main frame class ( like Class App )
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
    FillControlPanel(m_pControlPanel);



}

NEFrame::~NEFrame() {



    //cleanup
    delete m_pNodesDB;
    delete m_pLinker;
    delete m_pControlPanel;
    delete m_pNodesEditor;
    delete m_pFileHandler;
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
