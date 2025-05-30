#include "NodesEditor.hpp"

NodesEditor::NodesEditor(
    NodesDB* nodesDB,
    Linker* linker,
    ControlPanel* controlPanel
){
    this->nodesDB = nodesDB;
    this->linker = linker;
    this->controlPanel = controlPanel;
    
    this->padding = ImVec2(10, 10);

    this->fieldPos = new Vec2(0.0f, 0.0f);
    this->lastMausePos = std::make_shared<Vec2<float>>(0.0f, 0.0f);

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
}

void NodesEditor::draw(ImVec2 pos, ImVec2 size)
{
    pushStyles();

    ImGui::SetNextWindowSize(size);
    ImGui::SetNextWindowPos(pos);
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
            this->fieldPos->getX(), 
            this->fieldPos->getY()
        )
    );


    ImNodes::BeginNodeEditor();

    this->nodesDB->doOverNodes(&this->drawNodes);
    this->nodesDB->doOverLinks(&this->drawLinks);

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
            this->padding
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

void NodesEditor::drawCreationWindow(ImVec2 editorPos, ImVec2 editorSize)
{
    this->controlPanel->draw(
        getCorrectCoord(
            ImVec2(
                this->lastMausePos->getX(),
                this->lastMausePos->getY()
            ),
            editorPos,
            editorSize
        )
    );
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

        else if (ImGui::IsMouseClicked(this->controlPanelButtonNumber)) // Проверка на нажатие ближней боковой кнопки мыши
        {
            updateLastMausePos();
            this->controlPanel->activate();
        }
    }
}

void NodesEditor::moveField()
{
    ImVec2 mousePos = ImGui::GetMousePos();

    this->fieldPos->setX(fieldPos->getX() + mousePos.x - lastMausePos->getX());
    this->fieldPos->setY(fieldPos->getY() + mousePos.y - lastMausePos->getY());

    lastMausePos->setX(mousePos.x);
    lastMausePos->setY(mousePos.y);
}

void NodesEditor::updateLastMausePos()
{
    ImVec2 mousePos = ImGui::GetMousePos();

    lastMausePos->setX(mousePos.x);
    lastMausePos->setY(mousePos.y);
}

ImVec2 NodesEditor::getCorrectCoord(ImVec2 winPos, ImVec2 editorPos, ImVec2 editorSize)
{
    ImVec2 correctPos = ImVec2(
        winPos.x,
        winPos.y
    );

    ImVec2 winSize = this->controlPanel->getSize();

    float rigthX = editorPos.x + editorSize.x;
    float rigthY = editorPos.y + editorSize.y;

    if (winPos.x + winSize.x - this->padding.x > rigthX)
    {
        correctPos.x = rigthX - winSize.x - this->padding.x;
    }

    if (winPos.y + winSize.y - this->padding.y > rigthY)
    {
        correctPos.y = editorPos.y + editorSize.y - winSize.y - this->padding.y;
    }

    return correctPos;
}
