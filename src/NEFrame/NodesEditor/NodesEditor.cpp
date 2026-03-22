#include "NodesEditor.hpp"

#include <Windows.h>
#include <imnodes/imnodes.h>
#include <imgui/imgui.h>

#include "NEFrame/Formating/MouseButtons.hpp"
#include "NEFrame/Linker/Linker.hpp"
#include "ControlPanel/ControlPanel.hpp"
#include "NEFrame/NodesDB/NodesDB.hpp"

NodesEditor::NodesEditor(
    NodesDB* nodesDB,
    Linker* linker,
    ControlPanel* controlPanel
){
    this->nodesDB = nodesDB;
    this->linker = linker;
    this->controlPanel = controlPanel;


    this->padding = new ImVec2(10, 10);
    this->fieldPos = new ImVec2(0, 0);
    this->lastMausePos = new ImVec2(0, 0);
    this->miniMapSizeHint = 0.15f;

    this->moveFieldButtonNumber = MouseButton::RIGHT;
    this->controlPanelButtonNumber = MouseButton::NEAR_SIDE;

    this->drawNodes = [](Node* node)
        {
            node->draw();
        };

    this->drawLinks = [](LinkInfo* linkInfo)
        {
            ImNodes::Link(
                linkInfo->getLinkID(),
                linkInfo->getOutPointID(),
                linkInfo->getInPointID()
            );
        };
}

NodesEditor::NodesEditor(const NODES_EDITOR_PARAMS& params) {
    this->nodesDB = params.pNodesDB;
    this->linker = params.pLinker;
    this->controlPanel = params.pControlPanel;


    this->padding = new ImVec2(10, 10);
    this->fieldPos = new ImVec2(0, 0);
    this->lastMausePos = new ImVec2(0, 0);
    this->miniMapSizeHint = 0.15f;

    this->moveFieldButtonNumber = MouseButton::RIGHT;
    this->controlPanelButtonNumber = MouseButton::NEAR_SIDE;

    this->drawNodes = [](Node* node)
        {
            node->draw();
        };

    this->drawLinks = [](LinkInfo* linkInfo)
        {
            ImNodes::Link(
                linkInfo->getLinkID(),
                linkInfo->getOutPointID(),
                linkInfo->getInPointID()
            );
        };
}

NodesEditor::~NodesEditor() {
    delete this->fieldPos;
    delete this->lastMausePos;
    delete this->padding;
}

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

void NodesEditor::setMoveFieldButton(MouseButton mouseButton)
{
    this->moveFieldButtonNumber = mouseButton;
}

void NodesEditor::setControlPanelButton(MouseButton mouseButton)
{
    this->moveFieldButtonNumber = mouseButton;
}

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

void NodesEditor::moveField()
{
    ImVec2 mousePos = ImGui::GetMousePos();

    this->fieldPos->x = (fieldPos->x + mousePos.x - lastMausePos->x);
    this->fieldPos->y = (fieldPos->y + mousePos.y - lastMausePos->y);

    lastMausePos->x = (mousePos.x);
    lastMausePos->y = (mousePos.y);
}

void NodesEditor::updateLastMausePos()
{
    ImVec2 mousePos = ImGui::GetMousePos();

    lastMausePos->x = mousePos.x;
    lastMausePos->y = mousePos.y;
}

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
