#include "RenderComponent.h"

namespace gfx
{

RenderComponent::RenderComponent()
: _mesh(nullptr), _texture(nullptr)
{
    std::cout << "RenderComponent: Constructor\n";
}

RenderComponent::~RenderComponent()
{
    std::cout << "RenderComponent: Destructor\n";
}

void RenderComponent::setMesh(std::shared_ptr<Mesh> mesh)
{
    _mesh = std::move(mesh);
}

const std::shared_ptr<Mesh> RenderComponent::getMesh() const
{
    return _mesh;
}

std::shared_ptr<Texture2D> RenderComponent::getTexture()
{
    return _texture;
}

void RenderComponent::setTexture(std::shared_ptr<Texture2D> texture)
{
    _texture = std::move(texture);
}

} // namespace