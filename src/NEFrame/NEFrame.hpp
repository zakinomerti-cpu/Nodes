#ifndef _NERAME_HPP_
#define _NERAME_HPP_

#include <imnodes/imnodes.h>
#include <iostream>

#include "WindowNE.hpp"
#include "Formating\Vec2.hpp"

#include "NodesEditor/NodesEditor.hpp"


class NEFrame {
private:
    NodesEditor* nodesEditor;

public:
    NEFrame(NodesEditor* nodesEditor);

    void draw(int width, int height);
};

#endif // _NERAME_HPP_