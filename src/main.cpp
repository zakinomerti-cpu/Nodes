#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")


//-----------------------------------------------------------------------------
// File: Main.cpp
// Copyright (c) NIKITOS-V. All rights pirated nahyi
//-----------------------------------------------------------------------------
#include "Platform.hpp"
#include "NeFrame/NEFrame.hpp"



//-----------------------------------------------------------------------------
// Name: main()
// Desc: Entry point for the application
//-----------------------------------------------------------------------------
int main(void) {



    // Create platform window (stack allocated, no need to delete)
    Platform plt(1024, 600, "Nodes editor");
    NEFrame neFrame;



    // Set up the update callback for rendering
    plt.onUpdate([&neFrame](int width, int height) {
        neFrame.draw(width, height);
    });



    // Main message loop
    while (!plt.shouldClose()) {
        plt.render();
    }

    return 0;
}