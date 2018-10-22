#pragma once

#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Transform.h"
#include "SceneObject.h"

class CameraStatic
{
    public:
        CameraStatic(glm::vec2 screenSize = glm::vec2(1024.0f,768.0f));
        virtual ~CameraStatic();

        scene::Transform& getTransform();
        
        void setTransform(const scene::Transform transform);

        void setLookAt(const glm::vec3 lookAt);
        const glm::vec3 getLookAt() const;

        void setScreenSize(int width, int height);

        glm::mat4& getViewMatrix();
        glm::mat4& getProjectionMatrix();        

    protected:
        virtual void updateCameraViewProjection();

        scene::Transform    _transform;

        glm::vec3           _lookAt;
        glm::vec2           _screenSize;

        glm::mat4           _cameraView;
        glm::mat4           _cameraProjection;
};