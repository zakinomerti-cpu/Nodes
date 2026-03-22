#include "Platform.hpp"

#include "GLFW/glfw3.h"
#include "imgui/imgui.h"
#include "imnodes/imnodes.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include "NEFrame/Formating/Fonts.hpp"

Platform::Platform(int width, int height, const char* title) {
    glfwInit();

    this->m_width = 0;
    this->m_height = 0;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

    this->nodesEditorWindow = glfwCreateWindow(width, height, title, NULL, NULL);

    if (!nodesEditorWindow) {
        glfwTerminate();

        return;
    }

    this->m_onStart = NULL;
    this->m_onUpdate = NULL;
    this->m_onDestroy = NULL;
    this->m_shouldClose = 0;

    glfwMakeContextCurrent(nodesEditorWindow);
    glfwSwapInterval(1);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImNodes::CreateContext();

    ImGuiIO& io = ImGui::GetIO();
    (void)io;

    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;

    //fillFonts(&io); // заполнение шрифтов
    Font::arial_18 = io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\Arial.ttf", 18); // Стандартный шрифт

    Font::arial_16 = io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\Arial.ttf", 16);
    Font::arial_20 = io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\Arial.ttf", 20);
    Font::arial_22 = io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\Arial.ttf", 22);
    Font::arial_24 = io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\Arial.ttf", 24);

    Font::calibri_16 = io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\Calibri.ttf", 16);
    Font::calibri_18 = io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\Calibri.ttf", 18);
    Font::calibri_20 = io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\Calibri.ttf", 20);
    Font::calibri_22 = io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\Calibri.ttf", 22);
    Font::calibri_24 = io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\Calibri.ttf", 24);

    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(nodesEditorWindow, true);
    ImGui_ImplOpenGL3_Init();
}

void Platform::onDestroy(std::function<void()> callback) {
    if (callback) {
        this->m_onDestroy = std::move(callback);
    }
}

void Platform::onStart(std::function<void()> callback) {
    if (callback) {
        this->m_onStart = std::move(callback);
    }
}

void Platform::onUpdate(std::function<void(int width, int height)> callback) {
    if (callback) {
        this->m_onUpdate = std::move(callback);
    }
}

int Platform::getWidth() {
    return this->m_width;
}

int Platform::getHeingt() {
    return this->m_height;
}

void Platform::init() {
    if (this->m_onStart) {
        this->m_onStart();
    }
}

void Platform::render() {
    if (glfwWindowShouldClose(nodesEditorWindow)) {
        this->m_shouldClose = true;

        if (this->m_onDestroy) {
            this->m_onDestroy();
        }

        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();

        ImNodes::DestroyContext();
        ImGui::DestroyContext();
        glfwDestroyWindow(this->nodesEditorWindow);
        glfwTerminate();

        return;
    }

    glfwPollEvents();
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    if (this->m_onUpdate) {
        this->m_onUpdate(this->m_width, this->m_height);
    }

    ImGui::Render();

    glfwGetFramebufferSize(nodesEditorWindow, &this->m_width, &this->m_height);
    glViewport(0, 0, this->m_width, m_height);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    glfwSwapBuffers(nodesEditorWindow);
}


char Platform::shouldClose() {
    return this->m_shouldClose;
}
