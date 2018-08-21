#include <iostream>
#include <fstream>
#include <cstdio>
#include <memory>
#include <vector>

#include "Window/Window.h"

#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_glfw_gl3.h"
#include "ImGui/ImguiWindowsFileIO.hpp"

#include "Graphics/LoadShader.h"
#include "Graphics/Image.h"
#include "Graphics/Texture2D.h"
#include "Graphics/Vertex.h"
#include "Graphics/Cube.hpp"
#include "Graphics/Renderer.h"

#include "Scene/SceneObject.h"

#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Editor/MainMenu.h"
#include "Editor/Editor.h"

int W_WIDTH = 1366;
int W_HEIGHT = 768;

std::vector<std::shared_ptr<SceneObject>> sceneObjects;

struct Config
{
    Config()
    {
        clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
    }

    ImVec4 clear_color;
};

static void error_callback(int error, const char* description)
{
    fprintf(stderr, "Error %d: %s\n", error, description);
}


int main()
{
    glfwSetErrorCallback(error_callback);

    Config cfg;

	Window win;
    gfx::Renderer renderer;

    win.createWindow(W_WIDTH, W_HEIGHT, 10, 40);
    win.setWindowTitle("VirtualBus C++ - Map Editor");

    glEnable(GL_CULL_FACE);

    EditorGUI editor(win.getWindow());
    
editor.setSceneObjects(&sceneObjects);
    

    //ImGui_ImplGlfwGL3_Init(win.getWindow(), true);

    bool show_main_menu = true;
    bool show_test_window = true;
    bool show_my_window = false;
    bool window_fileIO_visible = false;

    std::shared_ptr<SceneObject> scnObj(new SceneObject);

    std::shared_ptr<gfx::Texture2D> texture(new gfx::Texture2D("Data/brick.jpg") );

    std::shared_ptr<Cube> cube(new Cube);
    
    scnObj->setMesh(cube);
    scnObj->setTexture(texture);
    scnObj->setName("Cube001");


    sceneObjects.push_back(scnObj);



    std::cout << "Scene objects: " << sceneObjects.size() << '\n';

    //editor.setActiveSceneObject(scnObj.get());

    std::vector<std::string> defines = {};
    GLuint shaderID = ShaderLoader::loadShader("Data/shader.vert", "Data/shader.frag");

    // Get uniforms location
    unsigned int transformLoc = glGetUniformLocation(shaderID, "transform");

    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    glm::mat4 CameraMatrix = glm::lookAt(
        glm::vec3(0.0f, 0.0f, 3.0f),    // the position of your camera, in world space
        glm::vec3(0.0f, 0.0f, 0.0f),   // where you want to look at, in world space
        glm::vec3(0.0f, 1.0f, 0.0f)        // probably glm::vec3(0,1,0), but (0,-1,0) would make you looking upside-down, which can be great too
    );

    glm::mat4 projectionMatrix = glm::perspective(
        glm::radians(46.0f), // The vertical Field of View, in radians: the amount of "zoom". Think "camera lens". Usually between 90° (extra wide) and 30° (quite zoomed in)
        static_cast<float>(W_WIDTH) / static_cast<float>(W_HEIGHT),       // Aspect Ratio. Depends on the size of your window. Notice that 4/3 == 800/600 == 1280/960, sounds familiar ?
        0.1f,              // Near clipping plane. Keep as big as possible, or you'll get precision issues.
        1000.0f             // Far clipping plane. Keep as little as possible.
    );


    //ImGuiIO& guiIO = ImGui::GetIO();

    std::string mouseState;
    std::string keyboardState;

	while (win.isOpened())
    {
        glUseProgram(shaderID);

        glm::mat4 MVP = projectionMatrix * CameraMatrix * scnObj->getTransform().getModelMatrix();

        // Ustawiamy matryce obiektu, potem zmienić na MVP
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(MVP));

        //renderer.render();
        renderer.render(sceneObjects);

        /*
        if (guiIO.WantCaptureMouse)
            mouseState = "Captured";
        else
            mouseState = "Released"; 

        if (guiIO.WantCaptureKeyboard)
            keyboardState = "Captured";
        else
            keyboardState = "Released";

        {
            static float f = 0.0f;
            ImGui::Text("Hello, world!");

            // Position
            ImGui::DragFloat3("Position", (float*)&scnObj.getTransform().getPositionRef(), 0.01f, 0.0f, 0.0f);

            // Rotation
            ImGui::DragFloat3("Rotation", (float*)&scnObj.getTransform().getRotationRef(), 0.1f, 0.0f, 0.0f);

            // Scale
            ImGui::DragFloat3("Scale", (float*)&scnObj.getTransform().getScaleRef(), 0.1f, 0.0f, 0.0f);

            //ImGui::ColorEdit3("clear color", (float*)&cfg.clear_color);
            if (ImGui::Button("Open File dialog")) window_fileIO_visible ^= 1;
            //if (ImGui::Button("My Window")) show_my_window ^= 1;
            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
            ImGui::Text("Mouse state: %s", mouseState.c_str());
            ImGui::Text("Kayboard state: %s", keyboardState.c_str());
        }

        if (show_main_menu)
            MainMenu(&show_main_menu);
        
        if (show_object_properties) 
            ShowObjectProperties(&scnObj);

        if( window_fileIO_visible )
        {
            string save_file;
            std::vector<string> window_recent_files = {};
            if( fileIOWindow( save_file, window_recent_files, "Save", {"*.usr", "*.*"} ) )
            {
                window_fileIO_visible = false;
                if( !save_file.empty() )
                {
                    //window_recent_files.push_back( save_file );

                    //std::ofstream out_file( "file.txt", std::ios_base::trunc );          
                    //writeStuffToFile( out_file ); 
                    //out_file.close();

                    std::cout << "Writing to disk!\n";
                }
            }
        }  

        */
        //if (show_test_window)
        //{
        //    ImGui::SetNextWindowPos(ImVec2(650, 20), ImGuiCond_FirstUseEver);
        //    ImGui::ShowTestWindow(&show_test_window);
        //}
        
        
        //ImGui::Render();
        // Koniec renderingu GUI
        
        //ImGui::Render();

        editor.Render();

        win.swapBuffers();
        win.updateEvents();
	}

	//ImGui_ImplGlfwGL3_Shutdown();

	return 0;
}
