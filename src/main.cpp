#include <iostream>
#include <cstdio>
#include <memory>
#include <vector>
#include <algorithm>

#include "Window/Window.h"

#include "Graphics/Image.h"
#include "Graphics/Texture2D.h"
#include "Graphics/Mesh.h"
#include "Graphics/Renderer.h"
#include "Graphics/RenderComponent.h"

#include "Scene/SceneObject.h"
#include "Scene/CameraStatic.h"
#include "Scene/CameraFPS.h"

#include "Editor/Editor.h"

int W_WIDTH = 1366;
int W_HEIGHT = 768;

double lastxPos, lastYpos;

bool cameraActive = false;
// std::shared_ptr<CameraStatic> camera;
std::unique_ptr<CameraFPS> camera = nullptr;
std::unique_ptr<EditorGUI> editor = nullptr;
std::unique_ptr<gfx::Renderer> renderer = nullptr;


float pos = 0.0f;

template <typename T>
T clamp(const T& what, const T& a, const T& b)
{
       return std::min(b, std::max(what, a));
}

std::list<SceneObject*> renderList;

std::shared_ptr<SceneObject> rootObject;

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

void change_window_size_callback(GLFWwindow* window, int width, int height)
{
    camera->setScreenSize(width, height);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
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

void inspectSceneObject(SceneObject* object)
{
    if (object->getRenderComponent())
        renderList.push_back(object);

    for (int index = 0; index < object->getChildCount(); ++index)
    {
        SceneObject* child = object->getChildAt(index);
        std::cout << "Object name: " << child->getName() << std::endl;

        inspectSceneObject(child);
    }
}


int main()
{
    glfwSetErrorCallback(error_callback);

	//Window win;    

    std::shared_ptr<Window> window = std::make_shared<Window>();

    window->createWindow(W_WIDTH, W_HEIGHT, 10, 40);
    window->setWindowTitle("VirtualBus C++ - Map Editor");

    renderer.reset(new gfx::Renderer);
    editor.reset(new EditorGUI(window));

    rootObject.reset(new SceneObject(nullptr, "Root"));

    glfwSetMouseButtonCallback(window->getWindow(), mouse_button_callback);
    glfwSetKeyCallback(window->getWindow(), key_callback);
    glfwSetCharCallback(window->getWindow(), char_callback);
    glfwSetWindowSizeCallback(window->getWindow(), change_window_size_callback);
    glfwSetFramebufferSizeCallback(window->getWindow(), framebuffer_size_callback);

    editor->setRootObject(rootObject.get());
    
    // Object 1
    std::shared_ptr<SceneObject> scnObj(new SceneObject);
    std::shared_ptr<gfx::Texture2D> texture(new gfx::Texture2D("Data/brick.jpg") );
    std::shared_ptr<Mesh> mesh = std::make_shared<Mesh>();
    
    scnObj->setRenderComponent(std::make_shared<gfx::RenderComponent>());
    scnObj->getRenderComponent()->setMesh(mesh);
    scnObj->getRenderComponent()->setTexture(texture);
    scnObj->setName("Cube001");
    

    // Object 2
    std::shared_ptr<SceneObject> scnObj2(new SceneObject);
    
    scnObj2->setRenderComponent(std::make_shared<gfx::RenderComponent>());
    scnObj2->getRenderComponent()->setMesh(mesh);
    scnObj2->getRenderComponent()->setTexture(texture);
    scnObj2->setName("Cube002");
    scnObj2->setPosition(glm::vec3(-3.0f, 1.0f, -6.0f));


    // Object 3
    std::shared_ptr<SceneObject> scnObj3(new SceneObject);
    std::shared_ptr<gfx::Texture2D> crateTex(new gfx::Texture2D("Data/crate.jpg") );
    
    scnObj3->setRenderComponent(std::make_shared<gfx::RenderComponent>());
    scnObj3->getRenderComponent()->setMesh(mesh);
    scnObj3->getRenderComponent()->setTexture(crateTex);
    scnObj3->setName("Cube003");
    scnObj3->setPosition(glm::vec3(1.0f, 0.0f, -1.0f));

    scnObj2->addChild(scnObj3);

    rootObject->addChild(scnObj);
    rootObject->addChild(scnObj2);
    
    // Camera
    // camera.reset( new CameraStatic(glm::vec2(W_WIDTH, W_HEIGHT)) );
    camera.reset( new CameraFPS(glm::vec2(W_WIDTH, W_HEIGHT)) );
    camera->setLookAt(glm::vec3(0.0f, 0.0f, 0.0f));
    camera->getTransform().setPosition(glm::vec3(0.0f, 0.0f, 3.0f));

    editor->setActiveCamera(camera.get());

    inspectSceneObject(rootObject.get());


    renderer->setCamera(camera.get());

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


	while (window->isOpened())
    {   
        nbFrames++;


        timePhysicsCurr = glfwGetTime();
        deltaTime = timePhysicsCurr - timePhysicsPrev;
        timePhysicsPrev = timePhysicsCurr;

        deltaTime = std::max(0.0, deltaTime);
        accumulator += deltaTime;
        accumulator = clamp(accumulator, 0.0, MAX_ACCUMULATED_TIME);


        if(!editor->GUIhasFocus())
            processInput(window->getWindow(), deltaTime);

        while ( accumulator > TIME_STEP )
        {
            // fixed time stuff
            accumulator -= TIME_STEP;
        }

        renderer->render(renderList);

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

        glfwGetCursorPos(window->getWindow(), &xpos, &ypos);

        if (cameraActive)
        {   
            double dx = (xpos - lastxPos);
            double dy = (ypos - lastYpos);

            if(camera)
                camera->rotateFromMouse(dx, dy);
        }
        
        lastxPos = xpos;
        lastYpos = ypos; 

        editor->Render();

        window->swapBuffers();
        window->updateEvents();
	}

    renderer.reset();
    editor.reset();
	return 0;
}
