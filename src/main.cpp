#include <iostream>
#include <cstdio>
#include <memory>
#include <vector>
#include <algorithm>

#include "Window/Window.h"

#include "Graphics/Image.h"
#include "Graphics/Texture2D.h"
#include "Graphics/Cube.hpp"
#include "Graphics/Renderer.h"

#include "Scene/SceneObject.h"
#include "Scene/CameraStatic.h"
#include "Scene/CameraFPS.h"

#include "Editor/Editor.h"

//#include "Editor/MainWindow.h"

int W_WIDTH = 1366;
int W_HEIGHT = 768;

double lastxPos, lastYpos;

bool cameraActive = false;
// std::shared_ptr<CameraStatic> camera;
std::shared_ptr<CameraFPS> camera;

std::unique_ptr<EditorGUI> editor = nullptr;
//static ImGuiIO io;

float pos = 0.0f;

template <typename T>
T clamp(const T& what, const T& a, const T& b)
{
       return std::min(b, std::max(what, a));
}

std::vector<std::shared_ptr<SceneObject>> sceneObjects;

static void error_callback(int error, const char* description)
{
    fprintf(stderr, "Error %d: %s\n", error, description);
}

// Callback dla wciśnięcia klawiszy
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    ImGuiIO& io = ImGui::GetIO();
    if (action == GLFW_PRESS)
    {
        io.KeysDown[key] = true;
    }
    if (action == GLFW_RELEASE)
        io.KeysDown[key] = false;

    (void)mods; // Modifiers are not reliable across systems
    io.KeyCtrl = io.KeysDown[GLFW_KEY_LEFT_CONTROL] || io.KeysDown[GLFW_KEY_RIGHT_CONTROL];
    io.KeyShift = io.KeysDown[GLFW_KEY_LEFT_SHIFT] || io.KeysDown[GLFW_KEY_RIGHT_SHIFT];
    io.KeyAlt = io.KeysDown[GLFW_KEY_LEFT_ALT] || io.KeysDown[GLFW_KEY_RIGHT_ALT];
    io.KeySuper = io.KeysDown[GLFW_KEY_LEFT_SUPER] || io.KeysDown[GLFW_KEY_RIGHT_SUPER];
}

// Callback do wpisywania znaków
void char_callback(GLFWwindow*, unsigned int c)
{
    ImGuiIO& io = ImGui::GetIO();
    if (c > 0 && c < 0x10000)
        io.AddInputCharacter((unsigned short)c);
}

// Callback dla pojedynczych zdarzeń - przyciski myszy
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    //std::cout << "Mouse event\n";

    if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
    {
        //std::cout << "RMB pressed\n";
        cameraActive = true;
    }
    
     if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_RELEASE)
    {
        //std::cout << "RMB released\n";
        cameraActive = false;
    }

}

void processInput(GLFWwindow* window, double deltaTime)
{   
    if (cameraActive)
    {
        //std::cout << "Camera active\n";
    
        if (glfwGetKey( window, GLFW_KEY_D ) == GLFW_PRESS)
	    {
            camera->move(STRAFE_RIGHT, deltaTime);
	    }

	    if (glfwGetKey( window, GLFW_KEY_A ) == GLFW_PRESS)
	    {
            camera->move(STRAFE_LEFT, deltaTime);
	    }

        if (glfwGetKey( window, GLFW_KEY_W ) == GLFW_PRESS)
	    {
            camera->move(FORWARD, deltaTime);
	    }

        if (glfwGetKey( window, GLFW_KEY_S ) == GLFW_PRESS)
	    {
            camera->move(BACKWARD, deltaTime);
	    }
    } 
}


int main()
{
    
    glfwSetErrorCallback(error_callback);

	Window win;    

    win.createWindow(W_WIDTH, W_HEIGHT, 10, 40);
    win.setWindowTitle("VirtualBus C++ - Map Editor");

    gfx::Renderer renderer;
    editor.reset(new EditorGUI(win.getWindow()));

    glfwSetMouseButtonCallback(win.getWindow(), mouse_button_callback);
    glfwSetKeyCallback(win.getWindow(), key_callback);
    glfwSetCharCallback(win.getWindow(), char_callback);

    editor->setSceneObjects(&sceneObjects);
    
    // Object 1
    std::shared_ptr<SceneObject> scnObj(new SceneObject);
    std::shared_ptr<gfx::Texture2D> texture(new gfx::Texture2D("Data/brick.jpg") );
    std::shared_ptr<Cube> cube(new Cube);
    
    scnObj->setMesh(cube);
    scnObj->setTexture(texture);
    scnObj->setName("Cube001");

    sceneObjects.push_back(scnObj);
    

    // Object 2
    std::shared_ptr<SceneObject> scnObj2(new SceneObject);
    
    scnObj2->setMesh(cube);
    scnObj2->setTexture(texture);
    scnObj2->setName("Cube002");
    scnObj2->setPosition(glm::vec3(-3.0f, 1.0f, -6.0f));

    scnObj2->setParent(scnObj);

    sceneObjects.push_back(scnObj2);

    // Camera
    // camera.reset( new CameraStatic(glm::vec2(W_WIDTH, W_HEIGHT)) );
    camera.reset( new CameraFPS(glm::vec2(W_WIDTH, W_HEIGHT)) );
    camera->setLookAt(glm::vec3(0.0f, 0.0f, 0.0f));
    camera->getTransform().setPosition(glm::vec3(0.0f, 0.0f, 3.0f));

    editor->setActiveCamera(camera);

    std::cout << "Scene objects: " << sceneObjects.size() << '\n';

    std::string mouseState;
    std::string keyboardState;

    renderer.setCamera(camera);

    double xpos, ypos;

// Time calculation variables
    double deltaTime = 0.0;
    double accumulator = 0.0;

    const double TIME_STEP = 1/60.0f;
    const double MAX_ACCUMULATED_TIME = 1.0;

    double timePhysicsCurr;
    double timePhysicsPrev;
    timePhysicsPrev = timePhysicsCurr = glfwGetTime();

    //how long ago FPS counter was updated
    double lastFPSupdate = timePhysicsCurr;

    int nbFrames = 0;


	while (win.isOpened())
    {   
        nbFrames++;


        timePhysicsCurr = glfwGetTime();
        deltaTime = timePhysicsCurr - timePhysicsPrev;
        timePhysicsPrev = timePhysicsCurr;

        deltaTime = std::max(0.0, deltaTime);
        accumulator += deltaTime;
        accumulator = clamp(accumulator, 0.0, MAX_ACCUMULATED_TIME);


        if(!editor->GUIhasFocus())
            processInput(win.getWindow(), deltaTime);

        while ( accumulator > TIME_STEP )
        {
            // fixed time stuff

            accumulator -= TIME_STEP;
        }


        renderer.render(sceneObjects);

        /*
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

        glfwGetCursorPos(win.getWindow(), &xpos, &ypos);

        if (cameraActive)
        {   
            double dx = (xpos - lastxPos);
            double dy = (ypos - lastYpos);

            camera->rotateFromMouse(dx, dy);
        }
        
        lastxPos = xpos;
        lastYpos = ypos; 

        editor->Render();

        win.swapBuffers();
        win.updateEvents();

	}

	return 0;
}
