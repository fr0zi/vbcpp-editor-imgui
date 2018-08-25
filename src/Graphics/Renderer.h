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

            void addRenderObject(std::shared_ptr<SceneObject> object);
            void render();
            void render(std::vector<std::shared_ptr<SceneObject>>& scene);

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