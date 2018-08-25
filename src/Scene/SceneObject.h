#pragma once

#include <string>
#include <memory>

#include "Transform.h"
#include "../Graphics/Texture2D.h"
#include "../Graphics/Cube.hpp"


class SceneObject
{
    public:
        SceneObject(std::string name = "SceneObject");
        virtual ~SceneObject();

        scene::Transform& getTransform();
        
        void setTransform(const scene::Transform transform);
        
        std::shared_ptr<gfx::Texture2D> getTexture();
        
        void setTexture(std::shared_ptr<gfx::Texture2D> texture);

        void setMesh(std::shared_ptr<Cube> mesh);

        std::shared_ptr<Cube> getMesh();

        void setName(std::string name);

        const std::string getName() const;

    protected:
        std::string                     _name;
        scene::Transform                _transform;
        std::shared_ptr<gfx::Texture2D> _texture;
        std::shared_ptr<Cube>           _mesh;
};
