#include "Renderer.h"
#include "LoadShader.h"

#include <iostream>

namespace gfx
{
    Renderer::Renderer()
        : _clearColor(glm::vec4(0.7f, 0.7f, 0.9f, 1.0f))
    {
        shaderID = ShaderLoader::loadShader("Data/shader.vert", "Data/shader.frag");

        glEnable(GL_CULL_FACE);
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);

        //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }

    void Renderer::addRenderObject(std::shared_ptr<SceneObject> object)
    {
        _objects.push_back(object);
    }

    void Renderer::render()
    {
        clearScreen();

        for (auto obj : _objects)
        {
            if (obj->getTexture())
            {
                obj->getTexture()->bind();
            }

            if (obj->getMesh())
            {
                glBindVertexArray(obj->getMesh()->getVAO());

                glDrawElements(GL_TRIANGLES, obj->getMesh()->getIndexCount(), GL_UNSIGNED_INT, 0);

                glBindVertexArray(0);
            }
    
            obj->getTexture()->release();
        }
    }

    void Renderer::render(std::vector<std::shared_ptr<SceneObject>>& scene)
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

        for (auto obj : scene)
        {
            if (obj->getTexture())
            {
                obj->getTexture()->bind();
            }

            if (obj->getMesh())
            {

                glm::mat4 MVP = _activeCamera->getProjectionMatrix() * _activeCamera->getViewMatrix() * obj->getModelMatrix();            

                // Ustawiamy matryce obiektu, potem zmienić na MVP
                glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(MVP));

                glBindVertexArray(obj->getMesh()->getVAO());

                glDrawElements(GL_TRIANGLES, obj->getMesh()->getIndexCount(), GL_UNSIGNED_INT, 0);

                glBindVertexArray(0);
            }
    
            obj->getTexture()->release();
        }
    }

    void Renderer::setCamera(std::shared_ptr<CameraStatic> camera)
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