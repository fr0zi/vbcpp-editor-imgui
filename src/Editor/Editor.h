#pragma once

#include "../ImGui/imgui.h"
#include "../ImGui/imgui_impl_glfw_gl3.h"
#include "../ImGui/ImguiWindowsFileIO.hpp"

#include "../Scene/SceneObject.h"
#include "../Scene/CameraFPS.h"
#include "../Window/Window.h"

#include <iostream>
#include <cstring>


class EditorGUI
{
    public:
    EditorGUI(std::shared_ptr<Window> window)
    : _selectedObject(nullptr), _activeCamera(nullptr), _OGLwindow(nullptr),
      showObjectProperties(true),
      showDemo(false),
      showSceneGraph(true),
      showCameraFPSSettings(false),
      showFileIODialog(false),
      showAddSceneObjectDialog(false)
    {
        std::cout << "Editor: Constructor\n";
        _OGLwindow = std::move(window);
        ImGui_ImplGlfwGL3_Init(_OGLwindow->getWindow(), false);
    }

    ~EditorGUI()
    {
        std::cout << "Editor: Destructor\n";
        ImGui_ImplGlfwGL3_Shutdown();
    }

    void setActiveSceneObject(SceneObject* object)
    {
        _selectedObject = object;
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

        if (showFileIODialog)
        {
            drawFileIODialog();
        }

        if (showAddSceneObjectDialog)
        {
            drawAddSceneObjectDialog();
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
            if (ImGui::BeginMenu("Objects"))
            {
                if (ImGui::MenuItem("Add Scene Object...", NULL) ) { showAddSceneObjectDialog = true; };
                if (ImGui::MenuItem("File IO Dialog...", NULL) ) { showFileIODialog = true; };
                ImGui::EndMenu();
            }
            ImGui::EndMainMenuBar();
        }
    }

    void drawObjectProperties()
    {
        glm::vec2 glfwWindowSize = _OGLwindow->getWindowSize();
        
        if (ImGui::Begin("Object Properties", &showObjectProperties))
        {
            ImVec2 windowPos = ImGui::GetWindowPos();
            //ImGui::Text("Window position: %d, %d", static_cast<int>(windowPos.x), static_cast<int>(windowPos.y));

            ImVec2 windowSize = ImGui::GetWindowSize();
            //ImGui::Text("Window size: %d, %d", static_cast<int>(windowSize.x), static_cast<int>(windowSize.y));
            //ImGui::Text("GLFW Window size: %d, %d", static_cast<int>(glfwWindowSize.x), static_cast<int>(glfwWindowSize.y));

            if ((windowPos.x + windowSize.x) >  glfwWindowSize.x)
            {
                ImGui::SetWindowPos(ImVec2(glfwWindowSize.x - windowSize.x, windowPos.y));
            } else
            if ((windowPos.y + windowSize.y) >  glfwWindowSize.y)
            {
                ImGui::SetWindowPos(ImVec2(windowPos.x, glfwWindowSize.y - windowSize.y));
            }

            if (_selectedObject)
            {
                // Object's name
                char buffer[50];

                strncpy(buffer, _selectedObject->getName().c_str(), sizeof buffer);
                
                buffer[sizeof buffer - 1] = '\0';

                if (ImGui::InputText("Name", buffer, IM_ARRAYSIZE(buffer), 
                                        ImGuiInputTextFlags_EnterReturnsTrue ) )
                {
                    _selectedObject->setName(std::string(buffer));
                }   

                ImGui::Separator();

                // Objects transformation
                ImGui::Text("Transformation");

                // Position
                ImGui::DragFloat3("Position", (float*)&_selectedObject->getPositionRef(), 0.01f, 0.0f, 0.0f);

                // Rotation
                ImGui::DragFloat3("Rotation", (float*)&_selectedObject->getRotationRef(), 0.1f, 0.0f, 0.0f);

                // Scale
                ImGui::DragFloat3("Scale", (float*)&_selectedObject->getScaleRef(), 0.1f, 0.0f, 0.0f);

                ImGui::Separator();
                ImGui::Text("COMPONENTS");

                if (_selectedObject->getRenderComponent() )
                {
                    if (ImGui::CollapsingHeader("Render Component"))
                    {
                        if (_selectedObject->getRenderComponent()->getMesh())
                        {
                            //ImGui::Text("Mesh");
                            unsigned int vertexCount = _selectedObject->getRenderComponent()->getMesh()->getVertexCount();
                            ImGui::Text("Vertex count: %d", vertexCount);
                        }

                        if (_selectedObject->getRenderComponent()->getTexture())
                        {
                            ImGui::Text("Texture image: %s", 
                                _selectedObject->getRenderComponent()->getTexture()->getImage()->getName().c_str());

                            ImTextureID texture = 
                                reinterpret_cast<void*>(_selectedObject->getRenderComponent()->getTexture()->getID());
                            
                            ImVec2 textureSize = ImVec2(128.0f, 128.0f);
                            ImGui::Image(texture, textureSize, ImVec2(0,0), ImVec2(1,1), 
                                            ImColor(255,255,255,255), ImColor(255,255,255,128)
                                        );
                        }
                    }
                } // CollapsingHeader("Render Component")


                if (false /* additional Component */)
                {
                    // show Component stuff here
                }
            }
        }
        ImGui::End();
    }

    void drawSceneGraph()
    {
        if (ImGui::Begin("Scene Graph", &showObjectProperties))
        {
            if (_rootObject)
            {
                for (int index = 0; index < _rootObject->getChildCount(); ++index)
                {
                    SceneObject* scnObj = _rootObject->getChildAt(index);
                    inspectSceneObject(scnObj);              
                }
            }
            ImGui::End();
        }
    }

    void inspectSceneObject(SceneObject* object)
    {
        ImGuiTreeNodeFlags node_flags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick;

        ImGui::PushID(object);
        //bool node_open = ImGui::TreeNode(object->getName().c_str());
        bool node_open = ImGui::TreeNodeEx((void*)(intptr_t)object, node_flags, object->getName().c_str());

        if (ImGui::IsItemClicked())
            _selectedObject = object;
        if (node_open)
        {
            for (int index = 0; index < object->getChildCount(); ++index)
            {
                SceneObject* child = object->getChildAt(index);
                    
                ImGui::PushID(child);

                inspectSceneObject(child);

                ImGui::PopID();                
            }
            ImGui::TreePop();
        }
        ImGui::PopID();
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

    void drawAddSceneObjectDialog()
    {
        std::string name;
        if (addSceneObjectDialog(name))
        {
            showAddSceneObjectDialog = false;

            if (!name.empty())
            {
                if (_selectedObject)
                    _selectedObject->addChild(std::make_shared<SceneObject>(nullptr, name));
                else
                    _rootObject->addChild(std::make_shared<SceneObject>(nullptr, name));
            }
            else
            {
                std::cout << "Name empty!" << std::endl;
            }
        }
    }

    bool GUIhasFocus()
    {
        return (ImGui::GetIO().WantCaptureMouse || ImGui::GetIO().WantCaptureKeyboard);
    }

    ImGuiIO& getIO()
    {
        return io;//ImGui::GetIO();
    }

    // Dialog windows

    bool drawFileIODialog()
    {
            string save_file;
            std::vector<string> window_recent_files = {};
            if( fileIOWindow( save_file, window_recent_files, "Save", {"*.usr", "*.*"} ) )
            {
                showFileIODialog = false;
                if( !save_file.empty() )
                {
                    //window_recent_files.push_back( save_file );

                    //std::ofstream out_file( "file.txt", std::ios_base::trunc );          
                    //writeStuffToFile( out_file ); 
                    //out_file.close();

                    std::cout << "Writing to disk!\n";
                }
            }
        return true;
    }

    bool addSceneObjectDialog(std::string& name)
    {
        bool close_it = false;

        static char objectName[50]; 

        ImVec2 size = ImVec2(300.0f, 100.0f);

        ImGui::SetNextWindowSize( size );
        ImGui::Begin( "Add SceneObject..." );

        ImGui::InputText("Name", objectName, IM_ARRAYSIZE(objectName) );

        if( ImGui::Button( "Create" ) )
        {
            name = std::string(objectName);
            close_it = true;
        }

        ImGui::SameLine();

        if( ImGui::Button( "Cancel" ) )
        {
            strncpy(objectName, "", sizeof objectName);
            close_it = true;
        }
        ImGui::End();

        return close_it;
    }

    void setActiveCamera(CameraFPS* camera)
    {
        _activeCamera = camera;
    }

    void setRootObject(SceneObject* root)
    {
        _rootObject = root;
    }

    private:
        ImGuiIO io;

        SceneObject* _selectedObject;
        SceneObject* _rootObject;

        CameraFPS* _activeCamera;

        std::shared_ptr<Window> _OGLwindow;

        bool showObjectProperties;
        bool showDemo;
        bool showSceneGraph;
        bool showCameraFPSSettings;
        bool showFileIODialog;
        bool showAddSceneObjectDialog;
};
