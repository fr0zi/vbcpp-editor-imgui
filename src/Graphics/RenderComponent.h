#pragma once

#include "../Core/Component.h"
#include "Mesh.h"
#include "Texture2D.h"

#include <vector>
#include <memory>
#include <iostream>

#include "Vertex.h"
#include "glm/glm.hpp"

// GLFW, GLEW
#include "GL/glew.h"

// Include GLU header with GLFW
#define GLFW_INCLUDE_GLU
#include "GLFW/glfw3.h"

namespace gfx
{

class RenderComponent : public virtual core::Component
{
    public:
        RenderComponent();
        virtual ~RenderComponent();

        void setMesh(std::shared_ptr<Mesh> mesh);
        const std::shared_ptr<Mesh> getMesh() const;

        std::shared_ptr<Texture2D> getTexture();
        void setTexture(std::shared_ptr<Texture2D> texture);

    private:
        std::shared_ptr<Mesh>           _mesh;
        std::shared_ptr<Texture2D> _texture;
};

} // namespace