#pragma once

#include <vector>
#include <memory>

#include "../Scene/SceneObject.h"

#include "glm/glm.hpp"

namespace gfx
{

    class Renderer
    {
        public:
            Renderer();

            void addRenderObject(std::shared_ptr<SceneObject> object);
            void render();

            void setClearColor(const glm::vec4 color);
        
        private:
            std::vector<std::shared_ptr<SceneObject>> _objects;
            glm::vec4   _clearColor;

            void clearScreen();
    };

}