#ifndef _BASE_NODES_BUILDER_H_
#define _BASE_NODES_BUILDER_H_
#include <memory>
#include <functional>


//-----------------------------------------------------------------------------
// Forward declarations
//-----------------------------------------------------------------------------
class Node;
class ControlPanel;



//-----------------------------------------------------------------------------
// Structure for node builder creation parameters
//-----------------------------------------------------------------------------
struct NODE_BUILDER_PARAMS {
    std::function<std::shared_ptr<Node>()> pfnCreator;
    const char* pszClassName;
};



void FillControlPanel(ControlPanel*);

#endif