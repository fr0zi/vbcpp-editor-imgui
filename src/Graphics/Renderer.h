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
            ~Renderer();

            void render(std::list<SceneObject*>& root);
            //void render(std::shared_ptr<SceneObject> rootObject);

            void setCamera(CameraStatic* camera);

            void setClearColor(const glm::vec4 color);
        
        private:
            std::vector<std::shared_ptr<SceneObject>> _objects;
            glm::vec4   _clearColor;
            CameraStatic* _activeCamera;

            GLuint shaderID;

            void clearScreen();
    };

}