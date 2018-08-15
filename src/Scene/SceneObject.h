#ifndef SCENEOBJECT_H
#define SCENEOBJECT_H

#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Transform
{
    public:
    void setPosition( const glm::vec3 position )
    {
        _position = position;
    }

    void setRotation( const glm::vec3 rotation )
    {
        _rotation = rotation;
    }

    void setScale( const glm::vec3 scale )
    {
        _scale = scale;
    }

    glm::vec3& getPositionRef()
    {
        return _position;
    }

    glm::vec3& getRotationRef()
    {
        return _rotation;
    }

    glm::vec3& getScaleRef()
    {
        return _scale;
    }

    const glm::mat4& getModelMatrix()
    {
        updateModelMatrix();

        return _modelMatrix;
    }

    private:
        glm::mat4 _modelMatrix;
        glm::vec3 _position;
        glm::vec3 _rotation;
        glm::vec3 _scale = {1.0f, 1.0f, 1.0f};

    void updateModelMatrix()
    {
        _modelMatrix = glm::mat4(1.0f);

        _modelMatrix = glm::translate(_modelMatrix, _position);
        
        _modelMatrix *= glm::rotate( _modelMatrix, glm::radians( _rotation[0]), glm::vec3( 1.0f, 0.0f, 0.0f ) );
        _modelMatrix *= glm::rotate( _modelMatrix, glm::radians( _rotation[1]), glm::vec3( 0.0f, 1.0f, 0.0f ) );
        _modelMatrix *= glm::rotate( _modelMatrix, glm::radians( _rotation[2]), glm::vec3( 0.0f, 0.0f, 1.0f ) );

        _modelMatrix *= glm::scale( _modelMatrix, glm::vec3( _scale[0], _scale[1], _scale[2] ) );
    }
};

class SceneObject
{
    public:
        Transform& getTransform()
        {
            return _transform;
        }

        void setTransform(const Transform transform)
        {
            _transform = transform;
        }

    private:
        Transform _transform;
};

#endif // SCENEOBJECT_H