#pragma once

#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace scene
{
    class Transform
    {
        public:
        void setPosition( const glm::vec3 position );

        void setRotation( const glm::vec3 rotation );

        void setScale( const glm::vec3 scale );

        glm::vec3& getPositionRef();

        glm::vec3& getRotationRef();

        glm::vec3& getScaleRef();

        const glm::mat4& getModelMatrix();


        private:
            glm::mat4 _modelMatrix;
            glm::vec3 _position;
            glm::vec3 _rotation;
            glm::vec3 _scale = {1.0f, 1.0f, 1.0f};

        void updateModelMatrix();
    };

} // namespace