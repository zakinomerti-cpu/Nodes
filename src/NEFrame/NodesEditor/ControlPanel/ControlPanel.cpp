# include "ControlPanel.hpp"


ControlPanel::ControlPanel(
    ImVec2 size,
    NodesDB* nodesDB, 
    Linker* linker
){
    this->nodesDB = nodesDB;
    this->linker = linker;

    this->size = size;

    this->padding = ImVec2(
        this->size.x * 0.05f,
        this->size.x * 0.05f
    );

    this->buttonSizeHint = 0.35f;

    this->active = false;

    createMainMenu();
    createCreationMenu();

    changeToMainMenu();
}

ControlPanel::ControlPanel(const CONTROL_PANEL_PARAMS& params) {
    this->nodesDB = params.pNodesDB;
    this->linker = params.pLinker;

    this->size = params.vInitialSize;

    this->padding = ImVec2(
        this->size.x * 0.05f,
        this->size.x * 0.05f
    );

    this->buttonSizeHint = 0.35f;

    this->active = false;

    createMainMenu();
    createCreationMenu();

    changeToMainMenu();
}

ControlPanel::~ControlPanel()
{
    this->nodeBuilders.clear();
}

void ControlPanel::draw(ImVec2 pos)
{
    ImGui::PushStyleVar(
        ImGuiStyleVar_WindowPadding, 
        this->padding
    );

    ImGui::SetNextWindowPos(pos);

    ImGui::SetNextWindowSize(this->size);

    ImGui::Begin(
        " ", 
        0, 
        ImGuiWindowFlags_NoMove | 
        ImGuiWindowFlags_NoResize | 
        ImGuiWindowFlags_NoCollapse | 
        ImGuiWindowFlags_NoTitleBar
    );

    this->drawCurentMenu(pos);

    checkFocused();

    ImGui::End();

    ImGui::PopStyleVar();
}

ImVec2 ControlPanel::getSize()
{
    return this->size;
}

void ControlPanel::setSize(ImVec2 size)
{
    this->size = size;
}

void ControlPanel::activate()
{
    this->active = true;
}

void ControlPanel::deactivate()
{
    changeToMainMenu();

    this->active = false;
}

bool ControlPanel::isActive()
{
    return this->active;
}

void ControlPanel::addNodeBuilder(NodeBuilder nodeBuilder)
{
    this->nodeBuilders.emplace_back(nodeBuilder);
}

void ControlPanel::createMainMenu()
{
    this->drawMainMenu = [this](ImVec2 pos)
        {
            ImVec2 buttonSize = getButtonSize();

            if (ImGui::Button("Create node", buttonSize))
            {
                changeToCreationMenu();
            }

            else if (ImGui::Button("Delete", buttonSize))
            {
                this->linker->delSelectedNodes();
                this->linker->delSelectedLinks();

                deactivate();
            }
        };
}

void ControlPanel::createCreationMenu()
{
    this->drawCreationMenu = [this](ImVec2 pos)
        {
            ImVec2 buttonSize = getButtonSize();

            if (ImGui::Button("<-", buttonSize))
            {
                changeToMainMenu();

                return;
            }

            for (nblist::iterator iter = this->nodeBuilders.begin(); iter != this->nodeBuilders.end(); iter++)
            {
                if (ImGui::Button(iter->getNodeName().c_str(), buttonSize))
                {
                    this->nodesDB->addNode(
                        iter->setPos(pos)->build()
                    );

                    deactivate();

                    return;
                }
            }
        };
}

ImVec2 ControlPanel::getButtonSize()
{
    return ImVec2(
        this->size.x - this->padding.x * 2,
        this->size.y * this->buttonSizeHint - this->padding.y
    );
}

void ControlPanel::changeToMainMenu()
{
    this->drawCurentMenu = this->drawMainMenu;
}

void ControlPanel::changeToCreationMenu()
{
    this->drawCurentMenu = this->drawCreationMenu;
}

void ControlPanel::checkFocused()
{
    if (!ImGui::IsWindowFocused()) 
    {
        deactivate();
    }
}
