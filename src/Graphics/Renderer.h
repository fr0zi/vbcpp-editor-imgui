#pragma once

#include <vector>
#include <memory>

#include "../Scene/SceneObject.h"
#include "../Scene/CameraStatic.h"

#include "glm/glm.hpp"

namespace gfx
{

    class Renderer
    {
        public:
            Renderer();

            void render(std::list<SceneObject*>& root);
            void render(std::shared_ptr<SceneObject> rootObject);

            void setCamera(std::shared_ptr<CameraStatic> camera);

            void setClearColor(const glm::vec4 color);
        
        private:
            std::vector<std::shared_ptr<SceneObject>> _objects;
            glm::vec4   _clearColor;
            std::shared_ptr<CameraStatic> _activeCamera;

            GLuint shaderID;

            void clearScreen();
    };

}