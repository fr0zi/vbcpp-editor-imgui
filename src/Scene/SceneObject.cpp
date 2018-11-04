#include "SceneObject.h"

SceneObject::SceneObject(SceneObject* parent, std::string name)
    : _name(name), _renderComponent(nullptr), _drawAABBox(true)
{
    std::cout << "Object " << _name << ": Constructor\n";
}

SceneObject::~SceneObject()
{
    std::cout << "Object " << _name << ": Destructor\n";
}

gfx::RenderComponent* SceneObject::getRenderComponent()
{
    if (!_renderComponent)
        _renderComponent = std::make_unique<gfx::RenderComponent>();

    return _renderComponent.get();
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

std::shared_ptr<SceneObject> SceneObject::getParent()
{
    return _parent.lock();
}

void SceneObject::addChild(std::shared_ptr<SceneObject> child)
{
    if (child)
    {
        child->setParent( shared_from_this() );
        _children.push_back( std::move(child) );
    }
}

void SceneObject::removeChild(std::shared_ptr<SceneObject> child)
{
    for (auto it = _children.begin(); it != _children.end(); ++it)
    {
        if (*it == child)
        {
            std::cout << "Removing child..." << std::endl;
            (*it)->setParent(nullptr);
            _children.erase(it);
        }
    }
}

const int SceneObject::getChildCount() const noexcept
{
    return _children.size();
}

SceneObject* SceneObject::getChildAt(unsigned int index)
{
    auto it = _children.begin();
    
    if (it != _children.end())
    {
        std::advance(it, index);
        return (*it).get();

    }
    else
        return nullptr;
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

AABBox& SceneObject::getAABBox()
{
    return _aabbox;
}

bool SceneObject::getDrawAABBox()
{
    return _drawAABBox;
}

void SceneObject::setDrawAABBox(bool state)
{
    _drawAABBox = state;
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

    std::shared_ptr<SceneObject> parent = _parent.lock();
    if (parent)
        _modelMatrix = parent->getModelMatrix() * _modelMatrix;
}