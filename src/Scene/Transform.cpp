#include "Transform.h"

namespace scene
{

    void Transform::setPosition( const glm::vec3 position )
    {
        _position = position;
    }

    void Transform::setRotation( const glm::vec3 rotation )
    {
        _rotation = rotation;
    }

    void Transform::setScale( const glm::vec3 scale )
    {
        _scale = scale;
    }

    glm::vec3& Transform::getPositionRef()
    {
        return _position;
    }

    glm::vec3& Transform::getRotationRef()
    {
        return _rotation;
    }

    glm::vec3& Transform::getScaleRef()
    {
        return _scale;
    }

    const glm::mat4& Transform::getModelMatrix()
    {
        updateModelMatrix();

        return _modelMatrix;
    }

    void Transform::update()
    {
        updateModelMatrix();
    }

    void Transform::updateModelMatrix()
    {
        _modelMatrix = glm::mat4(1.0f);

        glm::mat4 pos = glm::mat4(1.0f);
        pos = glm::translate(_modelMatrix, _position);
        
        glm::mat4 rot = glm::mat4(1.0f);
        rot *= glm::rotate( _modelMatrix, glm::radians( _rotation[0]), glm::vec3( 1.0f, 0.0f, 0.0f ) );
        rot *= glm::rotate( _modelMatrix, glm::radians( _rotation[1]), glm::vec3( 0.0f, 1.0f, 0.0f ) );
        rot *= glm::rotate( _modelMatrix, glm::radians( _rotation[2]), glm::vec3( 0.0f, 0.0f, 1.0f ) );

        glm::mat4 s = glm::mat4(1.0f);
        s = glm::scale( _modelMatrix, glm::vec3( _scale[0], _scale[1], _scale[2] ) );

        _modelMatrix = pos * rot * s;
    }

}