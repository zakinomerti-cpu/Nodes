#include "NEFrame.hpp"

NEFrame::NEFrame(NodesEditor* nodesEditor) 
{
    this->nodesEditor = nodesEditor;
}

void NEFrame::draw(int width, int height) 
{
    this->nodesEditor->draw(
        ImVec2(
            0,
            0
        ),
        ImVec2(
            width,
            height
        )
    );
}
