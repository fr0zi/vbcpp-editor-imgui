#include "SceneObject.h"

SceneObject::SceneObject(SceneObject* parent, std::string name)
    : _parent(parent), _name(name), _texture(nullptr), _mesh(nullptr)
{

}

SceneObject::~SceneObject()
{

}

scene::Transform& SceneObject::getTransform()
{
    return _transform;
}

void SceneObject::setTransform(const scene::Transform transform)
{
    _transform = transform;
}

std::shared_ptr<gfx::Texture2D> SceneObject::getTexture()
{
    return _texture;
}

void SceneObject::setTexture(std::shared_ptr<gfx::Texture2D> texture)
{
    _texture = texture;
}

void SceneObject::setMesh(std::shared_ptr<Cube> mesh)
{
    _mesh = mesh;
}

std::shared_ptr<Cube> SceneObject::getMesh()
{
    return _mesh;
}

void SceneObject::setName(std::string name)
{
    _name = name;
}

const std::string SceneObject::getName() const
{
    return _name;
}

void SceneObject::setParent(std::shared_ptr<SceneObject> parent)
{
    _parent = parent;
}

SceneObject* SceneObject::getParent()
{
    return _parent.get();
}

void SceneObject::addChild(std::shared_ptr<SceneObject> child)
{
    child->setParent( shared_from_this() );
    _childern.push_back( child );
}

// Transform
void SceneObject::setPosition( const glm::vec3 position )
{
    _position = position;
}

void SceneObject::setRotation( const glm::vec3 rotation )
{
    _rotation = rotation;
}

void SceneObject::setScale( const glm::vec3 scale )
{
    _scale = scale;
}

glm::vec3& SceneObject::getPositionRef()
{
    return _position;
}

glm::vec3& SceneObject::getRotationRef()
{
    return _rotation;
}

glm::vec3& SceneObject::getScaleRef()
{
    return _scale;
}

const glm::mat4& SceneObject::getModelMatrix()
{
    updateModelMatrix();

    return _modelMatrix;
}

void SceneObject::updateModelMatrix()
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

    if (_parent)
        _modelMatrix = _parent->getModelMatrix() * _modelMatrix;
}