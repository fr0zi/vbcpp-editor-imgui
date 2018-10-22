#include "Renderer.h"
#include "LoadShader.h"

#include <iostream>

namespace gfx
{
    Renderer::Renderer()
        : _clearColor(glm::vec4(0.7f, 0.7f, 0.9f, 1.0f))
    {
        std::cout << "Renderer: Constructor\n";
        shaderID = ShaderLoader::loadShader("Data/shader.vert", "Data/shader.frag");

        glEnable(GL_CULL_FACE);
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);

        //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }

    Renderer::~Renderer()
    {
        std::cout << "Renderer: Destructor\n";
    }
    
    void Renderer::render(std::list<SceneObject*>& root)
    {
        clearScreen();

        glUseProgram(shaderID);

                // Get uniforms location
        unsigned int transformLoc = glGetUniformLocation(shaderID, "transform");


        if (!_activeCamera)
        {
            std::cout << "Error: No camera has been set!\n";
            return;
        }


        for (auto obj : root)
        {
            Mesh* mesh = nullptr;
            Texture2D* texture = nullptr;
            RenderComponent* renderComponent = obj->getRenderComponent().get();

            //if (renderComponent)
            //{
                if (renderComponent->getTexture())
                {
                    texture = renderComponent->getTexture().get();
                }

                if (obj->getRenderComponent()->getMesh())
                {
                    mesh = obj->getRenderComponent()->getMesh().get();
                }
            //}

            if (mesh)
            {
                if (texture)
                    texture->bind();

                glm::mat4 MVP = _activeCamera->getProjectionMatrix() * _activeCamera->getViewMatrix() * obj->getModelMatrix();            

                // Ustawiamy matryce obiektu, potem zmienić na MVP
                glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(MVP));

                glBindVertexArray(mesh->getVAO());

                glDrawElements(GL_TRIANGLES, mesh->getIndexCount(), GL_UNSIGNED_INT, 0);

                if (texture)
                    texture->release();

                glBindVertexArray(0);
            }
    
            //obj->getTexture()->release();
        }
    }
    /*
    void Renderer::render(std::shared_ptr<SceneObject> rootObject)
    {
        clearScreen();

        glUseProgram(shaderID);

                // Get uniforms location
        unsigned int transformLoc = glGetUniformLocation(shaderID, "transform");


        if (!_activeCamera)
        {
            std::cout << "Error: No camera has been set!\n";
            return;
        }

        for (auto i = 0; i < rootObject->getChildCount(); i++)
        {
            
            auto obj = rootObject->getChildAt(i);

            if (obj->getTexture())
            {
                obj->getTexture()->bind();
            }

            if (obj->getRenderComponent())
            {

                glm::mat4 MVP = _activeCamera->getProjectionMatrix() * _activeCamera->getViewMatrix() * obj->getModelMatrix();            

                // Ustawiamy matryce obiektu, potem zmienić na MVP
                glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(MVP));

                glBindVertexArray(obj->getRenderComponent()->getVAO());

                glDrawElements(GL_TRIANGLES, obj->getRenderComponent()->getIndexCount(), GL_UNSIGNED_INT, 0);

                glBindVertexArray(0);
            }
    
            obj->getTexture()->release();
            
        }
    }
    */
    void Renderer::setCamera(CameraStatic* camera)
    {
        _activeCamera = camera;
    }

    void Renderer::setClearColor(const glm::vec4 color)
    {
        _clearColor = color;
    }

    void Renderer::clearScreen()
    {
        glClearColor(_clearColor[0], _clearColor[1], _clearColor[2], _clearColor[3]);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

} // namespace