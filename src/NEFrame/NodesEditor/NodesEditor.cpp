//-----------------------------------------------------------------------------
// File: NodesEditor.cpp
// Copyright (c) NIKITOS-V. All rights pirated nahyi
//-----------------------------------------------------------------------------
#include "NodesEditor.hpp"


// imgui
#include <imgui/imgui.h>
#include <imnodes/imnodes.h>


// neframe core components
#include "NEFrame/Formating/MouseButtons.hpp"
#include "NEFrame/NodesDB/NodesDB.hpp"
#include "NEFrame/Linker/Linker.hpp"
#include "NEFrame/BaseNodes.hpp"


// control panel node definition
#include "ControlPanel/ControlPanel.hpp"


//windows system header
#include <Windows.h>



//-----------------------------------------------------------------------------
// Name: NEFrame()
// Desc: Constructor for the main frame class ( like Class App )
//-----------------------------------------------------------------------------
NodesEditor::NodesEditor(const NODES_EDITOR_PARAMS& params) {



    // initial core componets
    this->nodesDB         = params.pNodesDB;
    this->linker          = params.pLinker;
    


    CONTROL_PANEL_PARAMS cpParams;
    cpParams.vInitialSize = ImVec2(200, 150);
    cpParams.pLinker = this->linker;
    cpParams.pNodesDB = this->nodesDB;
    this->controlPanel = new ControlPanel(cpParams);
    FillControlPanel(this->controlPanel);



    // create core components
    this->padding         = new ImVec2(10, 10);
    this->fieldPos        = new ImVec2(0, 0);
    this->lastMausePos    = new ImVec2(0, 0);
    this->miniMapSizeHint = 0.15f;



    //  fill mouse button id's
    this->moveFieldButtonNumber     = MouseButton::RIGHT;
    this->controlPanelButtonNumber  = MouseButton::NEAR_SIDE;

    this->drawNodes = [](Node* node) {
            node->draw();
    };

    this->drawLinks = [](LinkInfo* linkInfo) {
            ImNodes::Link(
                linkInfo->getLinkID(),
                linkInfo->getOutPointID(),
                linkInfo->getInPointID()
            );
     };
}



//-----------------------------------------------------------------------------
// Name: NEFrame()
// Desc: Destructor for the main frame class ( like Class App )
//-----------------------------------------------------------------------------
NodesEditor::~NodesEditor() {
    delete this->fieldPos;
    delete this->lastMausePos;
    delete this->padding;
}



//-----------------------------------------------------------------------------
// Name: NEFrame()
// Desc: Destructor for the main frame class ( like Class App )
//-----------------------------------------------------------------------------
void NodesEditor::draw(ImVec2* pos, ImVec2* size)
{
    pushStyles();

    ImGui::SetNextWindowSize(*size);
    ImGui::SetNextWindowPos(*pos);
    ImGui::Begin(
        "nodes",
        0,
        ImGuiWindowFlags_NoMove |
        ImGuiWindowFlags_NoResize |
        ImGuiWindowFlags_NoTitleBar |
        ImGuiWindowFlags_NoBackground
    );

    ImNodes::EditorContextResetPanning(
        ImVec2(
            this->fieldPos->x,
            this->fieldPos->y
        )
    );

    ImNodes::BeginNodeEditor();

    this->nodesDB->doOverNodes(this->drawNodes);
    this->nodesDB->doOverLinks(this->drawLinks);

    checkMouseEvents();

    ImNodes::MiniMap(this->miniMapSizeHint);

    ImNodes::EndNodeEditor();

    ImGui::End();

    popStyles();

    this->linker->checkNewLinks();

    if (this->controlPanel->isActive())
    {
        drawCreationWindow(pos, size);
    }
}



//-----------------------------------------------------------------------------
// Name: NEFrame()
// Desc: Destructor for the main frame class ( like Class App )
//-----------------------------------------------------------------------------
void NodesEditor::setMoveFieldButton(MouseButton mouseButton)
{
    this->moveFieldButtonNumber = mouseButton;
}

void NodesEditor::setControlPanelButton(MouseButton mouseButton)
{
    this->moveFieldButtonNumber = mouseButton;
}



//-----------------------------------------------------------------------------
// Name: NEFrame()
// Desc: Destructor for the main frame class ( like Class App )
//-----------------------------------------------------------------------------
void NodesEditor::pushStyles()
{
    { // Цвет звязи
        ImNodes::PushColorStyle(
            ImNodesCol_Link,
            IM_COL32(28, 104, 194, 250)
        );

        ImNodes::PushColorStyle(
            ImNodesCol_LinkHovered,
            IM_COL32(28, 104, 194, 250)
        );

        ImNodes::PushColorStyle(
            ImNodesCol_LinkSelected,
            IM_COL32(48, 144, 214, 255)
        );
    }

    { // Настройки / цвет поля с нодами
        ImGui::PushStyleVar(
            ImGuiStyleVar_WindowPadding,
            *this->padding
        );

        ImNodes::PushColorStyle(
            ImNodesCol_GridBackground,
            IM_COL32(40, 40, 40, 255)
        );
    }
}

void NodesEditor::popStyles()
{
    { // Для связей
        ImNodes::PopColorStyle();
        ImNodes::PopColorStyle();
        ImNodes::PopColorStyle();
    }

    { // Для поля с нодами
        ImNodes::PopColorStyle();
        ImGui::PopStyleVar();
    }
}



//-----------------------------------------------------------------------------
// Name: NEFrame()
// Desc: Destructor for the main frame class ( like Class App )
//-----------------------------------------------------------------------------
void NodesEditor::drawCreationWindow(ImVec2* editorPos, ImVec2* editorSize)
{
    ImVec2 winPos = ImVec2(this->lastMausePos->x, this->lastMausePos->y);
    this->controlPanel->draw(*getCorrectCoord(&winPos, editorPos, editorSize));
}

void NodesEditor::checkMouseEvents()
{
    if (ImNodes::IsEditorHovered())
    {
        if (ImGui::IsMouseClicked(this->moveFieldButtonNumber)) // Проверка на нажатие правой кнопки мыши
        {
            updateLastMausePos();
            this->controlPanel->deactivate();
        }

        else if (ImGui::IsMouseDown(this->moveFieldButtonNumber)) // Проверка на зажатие правой кнопки мыши
        {
            moveField();
            this->controlPanel->deactivate();
        }

        else if ((GetAsyncKeyState(VK_SHIFT) & 0x8000) && (GetAsyncKeyState('A') & 0x8000)) // Проверка на нажатие shift+A
        {
            updateLastMausePos();
            this->controlPanel->activate();
        }
    }
}



//-----------------------------------------------------------------------------
// Name: NEFrame()
// Desc: Destructor for the main frame class ( like Class App )
//-----------------------------------------------------------------------------
void NodesEditor::moveField() {
    ImVec2 mousePos = ImGui::GetMousePos();

    this->fieldPos->x = (fieldPos->x + mousePos.x - lastMausePos->x);
    this->fieldPos->y = (fieldPos->y + mousePos.y - lastMausePos->y);

    lastMausePos->x = (mousePos.x);
    lastMausePos->y = (mousePos.y);
}



//-----------------------------------------------------------------------------
// Name: NEFrame()
// Desc: Destructor for the main frame class ( like Class App )
//-----------------------------------------------------------------------------
void NodesEditor::updateLastMausePos() {
    ImVec2 mousePos = ImGui::GetMousePos();

    lastMausePos->x = mousePos.x;
    lastMausePos->y = mousePos.y;
}



//-----------------------------------------------------------------------------
// Name: NEFrame()
// Desc: Destructor for the main frame class ( like Class App )
//-----------------------------------------------------------------------------
ImVec2* NodesEditor::getCorrectCoord(ImVec2* winPos, ImVec2* editorPos, ImVec2* editorSize)
{
    ImVec2* correctPos = (ImVec2*)malloc(sizeof(ImVec2));
    *correctPos = ImVec2(winPos->x, winPos->y);

    ImVec2 winSize = this->controlPanel->getSize();

    float rigthX = editorPos->x + editorSize->x;
    float rigthY = editorPos->y + editorSize->y;

    if (winPos->x + winSize.x - this->padding->x > rigthX)
    {
        correctPos->x = rigthX - winSize.x - this->padding->x;
    }

    if (winPos->y + winSize.y - this->padding->y > rigthY)
    {
        correctPos->y = editorPos->y + editorSize->y - winSize.y - this->padding->y;
    }

    return correctPos;
}
