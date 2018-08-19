#include "Renderer.h"

#include <iostream>

namespace gfx
{
    Renderer::Renderer()
        : _clearColor(glm::vec4(0.7f, 0.7f, 0.9f, 1.0f))
    {

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

    void Renderer::setClearColor(const glm::vec4 color)
    {
        _clearColor = color;
    }

    void Renderer::clearScreen()
    {
        glClearColor(_clearColor[0], _clearColor[1], _clearColor[2], _clearColor[3]);
        glClear(GL_COLOR_BUFFER_BIT);
    }

} // namespace