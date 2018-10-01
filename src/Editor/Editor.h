#pragma once

#include "../ImGui/imgui.h"
#include "../ImGui/imgui_impl_glfw_gl3.h"
#include "../ImGui/ImguiWindowsFileIO.hpp"

#include "../Scene/SceneObject.h"
#include "../Scene/CameraFPS.h"

#include <iostream>
#include <cstring>


class EditorGUI
{
    public:
    EditorGUI(GLFWwindow* window)
    : _sceneObject(nullptr), _activeCamera(nullptr),
      showObjectProperties(true),
      showDemo(false),
      showSceneGraph(true),
      showCameraFPSSettings(false)
    {
        ImGui_ImplGlfwGL3_Init(window, false);
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
            ImGui::ShowTestWindow(&showDemo);
        }

        if (showCameraFPSSettings)
        {
            drawCameraFPSSettings();
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
            if (ImGui::BeginMenu("Windows"))
            {
                ImGui::MenuItem("Object Properties", NULL, &showObjectProperties);
                ImGui::MenuItem("CameraFPS Settings", NULL, &showCameraFPSSettings);
                ImGui::MenuItem("Demo", NULL, &showDemo);
                ImGui::EndMenu();
            }
            ImGui::EndMainMenuBar();
        }
    }

    void drawObjectProperties()
    {
        if (ImGui::Begin("Object Properties", &showObjectProperties))
        {
            if (_sceneObject)
            {
                // Object's name
                char buffer[50];

                strncpy(buffer, _sceneObject->getName().c_str(), sizeof buffer);
                
                buffer[sizeof buffer - 1] = '\0';

                if (ImGui::InputText("Name", buffer, IM_ARRAYSIZE(buffer), ImGuiInputTextFlags_EnterReturnsTrue ) )
                {
                    _sceneObject->setName(std::string(buffer));
                }   

                ImGui::Separator();

                // Objects transformation
                ImGui::Text("Transformation");

                //scene::Transform transform;

                //transform = _sceneObject->getTransform();
                // Position
                ImGui::DragFloat3("Position", (float*)&_sceneObject->getPositionRef(), 0.01f, 0.0f, 0.0f);

                // Rotation
                ImGui::DragFloat3("Rotation", (float*)&_sceneObject->getRotationRef(), 0.1f, 0.0f, 0.0f);

                // Scale
                ImGui::DragFloat3("Scale", (float*)&_sceneObject->getScaleRef(), 0.1f, 0.0f, 0.0f);

                //_sceneObject->setTransform(transform);
            }
        }
        ImGui::End();
    }

    void drawSceneGraph()
    {
        static int selection_mask = (1 << 2);
        static int node_clicked = -1;

        if (ImGui::Begin("Scene Graph", &showObjectProperties))
        {
            if (ImGui::TreeNode("Root"))
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
                    //bool node_open = ImGui::TreeNodeEx((void*)(intptr_t)counter, node_flags, "Selectable node %d", counter);
                    if (ImGui::IsItemClicked())
                    {
                        node_clicked = counter;
                        _sceneObject = scnObj.get();
                    }
                
                    if (node_open)
                    {
                        //ImGui::Text("Node selected, %d", node_clicked);
                        ImGui::TreePop();
                    }
                
                    //ImGui::TreePop();
                }
                ImGui::TreePop();
            
                if (node_clicked != -1)
                {
                    // Update selection state. Process outside of tree loop to avoid visual inconsistencies during the clicking-frame.
                    if (ImGui::GetIO().KeyCtrl)
                        selection_mask ^= (1 << node_clicked);          // CTRL+click to toggle
                    else //if (!(selection_mask & (1 << node_clicked))) // Depending on selection behavior you want, this commented bit preserve selection when clicking on item that is part of the selection
                        selection_mask = (1 << node_clicked);           // Click to single-select
                }
            }
        }
        ImGui::End();
    }

    void drawCameraFPSSettings()
    {
        if (ImGui::Begin("CameraFPS Settings", &showCameraFPSSettings))
        {
            if (_activeCamera)
            {
                float movementSpeed = _activeCamera->getMovementSpeed();
                float rotationSpeed = _activeCamera->getRotationSpeed();

                ImGui::DragFloat("Movement speed", &movementSpeed, 0.01f, 0.0f, 10.0f);

                // Rotation
                ImGui::DragFloat("Rotation speed", &rotationSpeed, 0.01f, 0.0f, 1.0f);

                _activeCamera->setMovementSpeed(movementSpeed);
                _activeCamera->setRotationSpeed(rotationSpeed);
            }
        }
        ImGui::End();
    }

    bool GUIhasFocus()
    {
        return (ImGui::GetIO().WantCaptureMouse || ImGui::GetIO().WantCaptureKeyboard);
    }

    ImGuiIO& getIO()
    {
        return io;//ImGui::GetIO();
    }

    void setActiveCamera(std::shared_ptr<CameraFPS> camera)
    {
        _activeCamera = camera;
    }

    private:
        ImGuiIO io;

        SceneObject* _sceneObject;
        std::vector<std::shared_ptr<SceneObject>>* _sceneObjects;

        std::shared_ptr<CameraFPS> _activeCamera;

        bool showObjectProperties;
        bool showDemo;
        bool showSceneGraph;
        bool showCameraFPSSettings;
};
