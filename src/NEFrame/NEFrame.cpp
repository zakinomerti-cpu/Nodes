//-----------------------------------------------------------------------------
// File: NEFrame.cpp
// Copyright (c) NIKITOS-V. All rights pirated nahyi2
//-----------------------------------------------------------------------------

#include "NEFrame.hpp"
#include "NEFrame/NodesEditor/NodesEditor.hpp"

#include "NEFrame/Linker/Linker.hpp"
#include "NEFrame/NodesDB/NodesDB.hpp"
#include "FileHandler.hpp"



//-----------------------------------------------------------------------------
// Name: NEFrame()
// Desc: Constructor for the main frame class ( like Class App )
//-----------------------------------------------------------------------------
NEFrame::NEFrame() {



    // Initialize core components
    m_pNodesDB = new NodesDB();
    m_pLinker = new Linker(m_pNodesDB);
    m_pFileHandler = new FileHandler();



    // Setup NodesEditor parameters
    NODES_EDITOR_PARAMS neParams;
    neParams.pNodesDB = m_pNodesDB;
    neParams.pLinker = m_pLinker;
    m_pNodesEditor = new NodesEditor(neParams);



}

NEFrame::~NEFrame() {



    //cleanup
    delete m_pNodesDB;
    delete m_pLinker;
    delete m_pNodesEditor;
    delete m_pFileHandler;
}



//-----------------------------------------------------------------------------
// Name: Draw()
// Desc: Renders the main frame and all its child components
//-----------------------------------------------------------------------------
void NEFrame::draw(int width, int height) {

    

    //window pos
    ImVec2 LeftUp = ImVec2(0, 0);
    ImVec2 RightDown = ImVec2(width, height);
    this->m_pNodesEditor->draw(&LeftUp, &RightDown);
}
