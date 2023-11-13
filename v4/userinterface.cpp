#include "userinterface.h"
#include "./imgui/imgui.h"
#include "./imgui/backends/imgui_impl_glfw.h"
#include "./imgui/backends/imgui_impl_opengl3.h"

UserInterface::UserInterface(PointLight* light, Object* o, GLFWwindow* window)
    :m_pl(light), m_o(o)
{

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330 core");


}

UserInterface::~UserInterface()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void UserInterface::Draw()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();/*
    ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_Always);
    ImGui::SetNextWindowSize(ImVec2(450, 350), ImGuiCond_Always);*/

    ImGui::Begin("My name is window, ImGUI window");
    ImGui::Text("Hello there adventurer!");
    ImGui::End();
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
