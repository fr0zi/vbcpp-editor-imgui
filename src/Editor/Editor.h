#pragma once

#include "../ImGui/imgui.h"
#include "../ImGui/imgui_impl_glfw_gl3.h"
#include "../ImGui/ImguiWindowsFileIO.hpp"

#include "../Scene/SceneObject.h"

#include <iostream>
#include <cstring>


class EditorGUI
{
    public:
    EditorGUI(GLFWwindow* window)
    {
        ImGui_ImplGlfwGL3_Init(window, true);
    }

    ~EditorGUI()
    {
        ImGui_ImplGlfwGL3_Shutdown();
    }

    void setActiveSceneObject(SceneObject* object)
    {
        _sceneObject = object;
    }

    void Render()
    {
        ImGui_ImplGlfwGL3_NewFrame();

        if (ImGui::BeginMainMenuBar())
        {
            if (ImGui::BeginMenu("File"))
            {
                //ShowExampleMenuFile();
                ImGui::EndMenu();
            }
            if (ImGui::BeginMenu("Edit"))
            {
                if (ImGui::MenuItem("Undo", "CTRL+Z")) {}
                if (ImGui::MenuItem("Redo", "CTRL+Y", false, false)) {}  // Disabled item
                ImGui::Separator();
                if (ImGui::MenuItem("Cut", "CTRL+X")) {}
                if (ImGui::MenuItem("Copy", "CTRL+C")) {}
                if (ImGui::MenuItem("Paste", "CTRL+V")) {}
                ImGui::EndMenu();
            }
            ImGui::EndMainMenuBar();
        }

        ImGui::Render();
    }

    private:
        SceneObject* _sceneObject;

        bool showObjectProperties;
};

namespace Editor
{
    static bool show_object_properties = false;

    IMGUI_API static void ObjectProperties(bool* p_open = NULL, SceneObject* object = nullptr)
    {
        ImGui::Text("Printing unusually long amount of text.");

        // Position
        ImGui::DragFloat3("Position", (float*)&object->getTransform().getPositionRef(), 0.01f, 0.0f, 0.0f);

        // Rotation
        ImGui::DragFloat3("Rotation", (float*)&object->getTransform().getRotationRef(), 0.1f, 0.0f, 0.0f);

        // Scale
        ImGui::DragFloat3("Scale", (float*)&object->getTransform().getScaleRef(), 0.1f, 0.0f, 0.0f);

        //char buffer[50];
        //strncpy(buffer, object->getTextureName().c_str(), sizeof buffer);
        //buffer[sizeof buffer - 1] = '\0';



        //if (ImGui::InputText("input text", buffer, IM_ARRAYSIZE(buffer), ImGuiInputTextFlags_EnterReturnsTrue ) )
        //{
        //    object->setTextureName(std::string(buffer));
        //}
    }

    IMGUI_API static void MainMenu(bool* p_open = NULL)
    {
        if (ImGui::BeginMainMenuBar())
        {
            if (ImGui::BeginMenu("Objects"))
            {
                ImGui::MenuItem("Properties", NULL, &show_object_properties);
                ImGui::EndMenu();
            }
            if (ImGui::BeginMenu("Edit"))
            {
                if (ImGui::MenuItem("Undo", "CTRL+Z")) {}
                if (ImGui::MenuItem("Redo", "CTRL+Y", false, false)) {}  // Disabled item
                ImGui::Separator();
                if (ImGui::MenuItem("Cut", "CTRL+X")) {}
                if (ImGui::MenuItem("Copy", "CTRL+C")) {}
                if (ImGui::MenuItem("Paste", "CTRL+V")) {}
                ImGui::EndMenu();
            }
            ImGui::EndMainMenuBar();
        }
    }

} // namespace




/*
class Editor
{
    public:
    Editor(Window* window)
    {
        ImGui_ImplGlfwGL3_Init(window->getWindow(), true);
    }

    ~Editor()
    {
        ImGui_ImplGlfwGL3_Shutdown();
    }

    void RenderGui()
    {
        ImGui_ImplGlfwGL3_NewFrame();

        if (ImGui::BeginMainMenuBar())
        {
            if (ImGui::BeginMenu("File"))
            {
                //ShowExampleMenuFile();
                ImGui::EndMenu();
            }
            if (ImGui::BeginMenu("Edit"))
            {
                if (ImGui::MenuItem("Undo", "CTRL+Z")) {}
                if (ImGui::MenuItem("Redo", "CTRL+Y", false, false)) {}  // Disabled item
                ImGui::Separator();
                if (ImGui::MenuItem("Cut", "CTRL+X")) {}
                if (ImGui::MenuItem("Copy", "CTRL+C")) {}
                if (ImGui::MenuItem("Paste", "CTRL+V")) {}
                ImGui::EndMenu();
            }
            ImGui::EndMainMenuBar();
        }

        ImGui::Render();
    }

    private:


};
*/