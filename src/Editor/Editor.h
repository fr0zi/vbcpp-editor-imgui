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
    : _sceneObject(nullptr),
      showObjectProperties(false),
      showDemo(true),
      showSceneGraph(true)
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

    void setSceneObjects(std::vector<std::shared_ptr<SceneObject>>* sceneObjects)
    {
        _sceneObjects = sceneObjects;
    }

    void Render()
    {
        ImGui_ImplGlfwGL3_NewFrame();

        drawMainMenu();

        if (showObjectProperties)
            drawObjectProperties();

        if (showSceneGraph)
            drawSceneGraph();

        if (showDemo)
        {
            //ImGui::SetNextWindowPos(ImVec2(650, 20), ImGuiCond_FirstUseEver);
            ImGui::ShowTestWindow(&showDemo);
        }

        ImGui::Render();
    }

    void drawMainMenu()
    {
        if( ImGui::BeginMainMenuBar() )
        {
            if ( ImGui::BeginMenu("File") )
            {
                //ShowExampleMenuFile();
                ImGui::EndMenu();
            }
            if (ImGui::BeginMenu("Objects"))
            {
                ImGui::MenuItem("Properties", NULL, &showObjectProperties);
                ImGui::EndMenu();
            }
            if ( ImGui::BeginMenu("Edit") )
            {
                if ( ImGui::MenuItem("Undo", "CTRL+Z") ) {}
                if ( ImGui::MenuItem("Redo", "CTRL+Y", false, false) ) {}  // Disabled item
                ImGui::Separator();
                if ( ImGui::MenuItem("Cut", "CTRL+X") ) {}
                if ( ImGui::MenuItem("Copy", "CTRL+C") ) {}
                if ( ImGui::MenuItem("Paste", "CTRL+V") ) {}
                ImGui::EndMenu();
            }
            ImGui::EndMainMenuBar();
        }
    }

    void drawObjectProperties()
    {
        ImGui::Text("Printing unusually long amount of text.");

        scene::Transform transform;

        if (_sceneObject)
            transform = _sceneObject->getTransform();
        // Position
        ImGui::DragFloat3("Position", (float*)&transform.getPositionRef(), 0.01f, 0.0f, 0.0f);

        // Rotation
        ImGui::DragFloat3("Rotation", (float*)&transform.getRotationRef(), 0.1f, 0.0f, 0.0f);

        // Scale
        ImGui::DragFloat3("Scale", (float*)&transform.getScaleRef(), 0.1f, 0.0f, 0.0f);

        if (_sceneObject)
            _sceneObject->setTransform(transform);
        //char buffer[50];
        //strncpy(buffer, object->getTextureName().c_str(), sizeof buffer);
        //buffer[sizeof buffer - 1] = '\0';



        //if (ImGui::InputText("input text", buffer, IM_ARRAYSIZE(buffer), ImGuiInputTextFlags_EnterReturnsTrue ) )
        //{
        //    object->setTextureName(std::string(buffer));
        //}
    }

    void drawSceneGraph()
    {
        static int selection_mask = (1 << 2);
        static int node_clicked = -1;

        if (ImGui::TreeNode("Advanced, with Selectable nodes"))
        {
            int counter = 0;
            
            for (; counter < _sceneObjects->size(); ++counter)
            {
                std::shared_ptr<SceneObject> scnObj = _sceneObjects->at(counter);

                // Disable the default open on single-click behavior and pass in Selected flag according to our selection state.
                    ImGuiTreeNodeFlags node_flags = ImGuiTreeNodeFlags_OpenOnArrow | 
                        ImGuiTreeNodeFlags_OpenOnDoubleClick | 
                        ((selection_mask & (1 << counter)) ? ImGuiTreeNodeFlags_Selected : 0);

                // Node
                bool node_open = ImGui::TreeNodeEx((void*)(intptr_t)counter, node_flags, scnObj->getName().c_str());
                if (ImGui::IsItemClicked())
                {
                    node_clicked = counter;
                    _sceneObject = scnObj.get();
                }

                if (node_open)
                {
                    ImGui::Text("Node selected, %d", node_clicked);
                    ImGui::TreePop();
                }
                
                ImGui::TreePop();
            }
            if (node_clicked != -1)
            {
                // Update selection state. Process outside of tree loop to avoid visual inconsistencies during the clicking-frame.
                if (ImGui::GetIO().KeyCtrl)
                    selection_mask ^= (1 << node_clicked);          // CTRL+click to toggle
                else //if (!(selection_mask & (1 << node_clicked))) // Depending on selection behavior you want, this commented bit preserve selection when clicking on item that is part of the selection
                    selection_mask = (1 << node_clicked);           // Click to single-select
            }
            //ImGui::TreePop();
        }

        
        //_sceneObject = scnObj.get();
    }

    private:
        SceneObject* _sceneObject;
        std::vector<std::shared_ptr<SceneObject>>* _sceneObjects;

        bool showObjectProperties;
        bool showDemo;
        bool showSceneGraph;
};

/*
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
*/
