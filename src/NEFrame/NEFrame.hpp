//-----------------------------------------------------------------------------
// File: NEFrame.hpp
// Copyright (c) NIKITOS-V. All rights pirated nahyi
//-----------------------------------------------------------------------------
#ifndef _NEFRAME_HPP_
#define _NEFRAME_HPP_



//-----------------------------------------------------------------------------
// Forward declarations
//-----------------------------------------------------------------------------
class NodesEditor;
class NodesDB;
class Linker;
class FileHandler;

class ControlPanel;



//-----------------------------------------------------------------------------
// Name: class NEFrame
// Desc: Main frame window class for node editor application
//-----------------------------------------------------------------------------
class NEFrame {
private:



    //-------------------------------------------------------------------------
    // Private member variables
    NodesEditor*    m_pNodesEditor;
    NodesDB*        m_pNodesDB;
    Linker*         m_pLinker;
    FileHandler*    m_pFileHandler;



    // main node
    ControlPanel*   m_pControlPanel;



public:



    //-------------------------------------------------------------------------
    // Public methods
    NEFrame();
    ~NEFrame();



    void draw(int width, int height);
};

#endif // _NEFRAME_HPP_