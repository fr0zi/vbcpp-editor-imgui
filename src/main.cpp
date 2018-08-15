#include <iostream>
#include <fstream>
#include <cstdio>
#include <memory>
#include <vector>

#include "Window/Window.h"

#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_glfw_gl3.h"
#include "ImGui/ImguiWindowsFileIO.hpp"

#include "Renderer/LoadShader.h"
#include "Renderer/VBImage.h"
#include "Renderer/Vertex.h"
#include "Renderer/Cube.hpp"

#include "Scene/SceneObject.h"

#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

int W_WIDTH = 1366;
int W_HEIGHT = 768;

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

SceneObject scnObj;

int main()
{
    glfwSetErrorCallback(error_callback);

    Config cfg;

	Window win;

    win.createWindow(W_WIDTH, W_HEIGHT, 10, 40);
    win.setWindowTitle("VirtualBus C++ - Map Editor");

    glEnable(GL_CULL_FACE);

    ImGui_ImplGlfwGL3_Init(win.getWindow(), true);

    bool show_test_window = true;
    bool show_my_window = false;
    bool window_fileIO_visible = false;

    std::shared_ptr<gfx::VBImage> image(new gfx::VBImage("Data/brick.jpg"));

    std::cout << "Image width: " << image->getWidth() << '\n';
    std::cout << "Image height: " << image->getHeight() << '\n';
    std::cout << "Image channels: " << image->getChannelCount() << '\n';

    std::shared_ptr<Cube> cube(new Cube);

    // ======================================
    unsigned int VBO;
    glGenBuffers(1, &VBO);

    unsigned int EBO;
    glGenBuffers(1, &EBO);

    unsigned int VAO;
    glGenVertexArrays(1, &VAO); 
    // ======================================

    unsigned int texture;
    glGenTextures(1, &texture);

    glBindTexture(GL_TEXTURE_2D, texture);
    // set the texture wrapping/filtering options (on the currently bound texture object)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image->getWidth(), image->getHeight(), 0, GL_RGB, GL_UNSIGNED_BYTE, image->getData());
    glGenerateMipmap(GL_TEXTURE_2D);

    //ShaderLoader shaderLoader;
    
    std::vector<std::string> defines = {};
    GLuint shaderID = ShaderLoader::loadShader("Data/shader.vert", "Data/shader.frag");

    // Get uniforms location
    unsigned int transformLoc = glGetUniformLocation(shaderID, "transform");

    // Vertex data
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, cube->getVertexCount() * sizeof(gfx::Vertex), cube->getVerticesData(), GL_STATIC_DRAW);

    // Index data
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, cube->getIndexCount() * sizeof(unsigned int), cube->getIndicesData(), GL_STATIC_DRAW);

    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);
    

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


    ImGuiIO& guiIO = ImGui::GetIO();

    std::string mouseState;
    std::string keyboardState;

	while (win.isOpened())
    {
        glClearColor(cfg.clear_color.x, cfg.clear_color.y, cfg.clear_color.z, cfg.clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderID);

        glm::mat4 MVP = projectionMatrix * CameraMatrix * scnObj.getTransform().getModelMatrix();

        // Ustawiamy matryce obiektu, potem zmienić na MVP
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(MVP));

        glBindTexture(GL_TEXTURE_2D, texture);
        glBindVertexArray(VAO);

        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

        glBindVertexArray(0);

        // Rendering GUI
        ImGui_ImplGlfwGL3_NewFrame();

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
            ImGui::DragFloat("Pos X", (float*)&scnObj.getTransform().getPositionRef().x, 0.01f);
            ImGui::DragFloat("Pos Y", (float*)&scnObj.getTransform().getPositionRef().y, 0.01f);
            ImGui::DragFloat("Pos Z", (float*)&scnObj.getTransform().getPositionRef().z, 0.01f);
            // Rotation
            ImGui::DragFloat("Rot X", (float*)&scnObj.getTransform().getRotationRef().x, 0.1f);
            ImGui::DragFloat("Rot Y", (float*)&scnObj.getTransform().getRotationRef().y, 0.1f);
            ImGui::DragFloat("Rot Z", (float*)&scnObj.getTransform().getRotationRef().z, 0.1f);
            // Scale
            ImGui::DragFloat("Scale X", (float*)&scnObj.getTransform().getScaleRef().x, 0.1f);
            ImGui::DragFloat("Scale Y", (float*)&scnObj.getTransform().getScaleRef().y, 0.1f);
            ImGui::DragFloat("Scale Z", (float*)&scnObj.getTransform().getScaleRef().z, 0.1f);

            ImGui::ColorEdit3("clear color", (float*)&cfg.clear_color);
            if (ImGui::Button("Open File dialog")) window_fileIO_visible ^= 1;
            if (ImGui::Button("My Window")) show_my_window ^= 1;
            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
            ImGui::Text("Mouse state: %s", mouseState.c_str());
            ImGui::Text("Kayboard state: %s", keyboardState.c_str());
        }

        
        if( window_fileIO_visible )
        {
            string save_file;
            std::vector<string> window_recent_files = {};
            if( fileIOWindow( save_file, window_recent_files, "Save", {"*.usr", "*.*"} ) )
            {
                window_fileIO_visible = false;
                if( !save_file.empty() )
                {
                    window_recent_files.push_back( save_file );

                    std::ofstream out_file( "file.txt", std::ios_base::trunc );          
                    //writeStuffToFile( out_file ); 
                    out_file.close();
                }
            }
        }  

        if (show_test_window)
        {
            ImGui::SetNextWindowPos(ImVec2(650, 20), ImGuiCond_FirstUseEver);
            ImGui::ShowTestWindow(&show_test_window);
        }
        
        
        ImGui::Render();
        // Koniec renderingu GUI

		win.swapBuffers();
        win.updateEvents();
	}

	ImGui_ImplGlfwGL3_Shutdown();

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

	return 0;
}
