#include "SceneObject.h"

SceneObject::SceneObject()
    : _texture(nullptr), _mesh(nullptr)
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