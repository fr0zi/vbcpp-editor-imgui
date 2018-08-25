#include <iostream>
#include <cstdio>
#include <memory>
#include <vector>

#include "Window/Window.h"

#include "Graphics/Image.h"
#include "Graphics/Texture2D.h"
#include "Graphics/Cube.hpp"
#include "Graphics/Renderer.h"

#include "Scene/SceneObject.h"
#include "Scene/CameraStatic.h"

#include "Editor/Editor.h"

int W_WIDTH = 1366;
int W_HEIGHT = 768;

bool cameraActive = false;
std::shared_ptr<CameraStatic> camera;

float pos = 0.0f;

std::vector<std::shared_ptr<SceneObject>> sceneObjects;

static void error_callback(int error, const char* description)
{
    fprintf(stderr, "Error %d: %s\n", error, description);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_L && action == GLFW_PRESS)
	{
		std::cout << "Key K pressed\n";
	}
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

void processInput(GLFWwindow* window)
{
    if (cameraActive)
    {
        //std::cout << "Camera active\n";
    
        if (glfwGetKey( window, GLFW_KEY_D ) == GLFW_PRESS)
	    {
            //std::cout << "Move right\n";
		    camera->getTransform().getPositionRef().x += 0.001f;
	    }

	    if (glfwGetKey( window, GLFW_KEY_A ) == GLFW_PRESS)
	    {
            //std::cout << "Move left\n";
		    camera->getTransform().getPositionRef().x -= 0.001f;
	    }

        if (glfwGetKey( window, GLFW_KEY_W ) == GLFW_PRESS)
	    {
            //std::cout << "Move left\n";
		    camera->getTransform().getPositionRef().z -= 0.001f;
	    }

        if (glfwGetKey( window, GLFW_KEY_S ) == GLFW_PRESS)
	    {
            //std::cout << "Move left\n";
		    camera->getTransform().getPositionRef().z += 0.001f;
	    }
    }

}

int main()
{
    glfwSetErrorCallback(error_callback);

	Window win;    

    win.createWindow(W_WIDTH, W_HEIGHT, 10, 40);
    win.setWindowTitle("VirtualBus C++ - Map Editor");

    glfwSetMouseButtonCallback(win.getWindow(), mouse_button_callback);
    glfwSetKeyCallback(win.getWindow(), key_callback);

    gfx::Renderer renderer;
    EditorGUI editor(win.getWindow());
    
    editor.setSceneObjects(&sceneObjects);
    
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
    //std::shared_ptr<gfx::Texture2D> texture2(new gfx::Texture2D("Data/brick.jpg") );
    //std::shared_ptr<Cube> cube2(new Cube);
    
    scnObj2->setMesh(cube);
    scnObj2->setTexture(texture);
    scnObj2->setName("Cube002");
    scnObj2->getTransform().setPosition(glm::vec3(-3.0f, 1.0f, -6.0f));

    sceneObjects.push_back(scnObj2);

    // Camera
    camera.reset( new CameraStatic(glm::vec2(W_WIDTH, W_HEIGHT)) );
    camera->setLookAt(glm::vec3(0.0f, 0.0f, 0.0f));
    camera->getTransform().setPosition(glm::vec3(0.0f, 0.0f, 3.0f));

    std::cout << "Scene objects: " << sceneObjects.size() << '\n';

    std::string mouseState;
    std::string keyboardState;

    renderer.setCamera(camera);

	while (win.isOpened())
    {   
        if(!editor.GUIhasFocus())
            processInput(win.getWindow());

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

        editor.Render();

        win.swapBuffers();
        win.updateEvents();

	}

	return 0;
}
