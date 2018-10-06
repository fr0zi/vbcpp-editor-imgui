#pragma once

#include <string>
#include <list>
#include <memory>

#include "Transform.h"
#include "../Graphics/Texture2D.h"
#include "../Graphics/Cube.hpp"

//typedef std::list<std::shared_ptr<SceneObject>> SceneObjectList;

class SceneObject : public std::enable_shared_from_this<SceneObject>
{
    public:
        SceneObject(SceneObject* parent = nullptr, std::string name = "SceneObject");
        virtual ~SceneObject();

        scene::Transform& getTransform();
        
        void setTransform(const scene::Transform transform);
        
        std::shared_ptr<gfx::Texture2D> getTexture();
        
        void setTexture(std::shared_ptr<gfx::Texture2D> texture);

        void setMesh(std::shared_ptr<Cube> mesh);

        std::shared_ptr<Cube> getMesh();

        void setName(std::string name);

        const std::string getName() const;

        void setParent(std::shared_ptr<SceneObject> parent);

        SceneObject* getParent();

        void addChild(std::shared_ptr<SceneObject> child);

        // Transform
        void setPosition( const glm::vec3 position );

        void setRotation( const glm::vec3 rotation );

        void setScale( const glm::vec3 scale );

        glm::vec3& getPositionRef();

        glm::vec3& getRotationRef();

        glm::vec3& getScaleRef();

        const glm::mat4& getModelMatrix(); 

    protected:
        std::shared_ptr<SceneObject>            _parent;
        std::list<std::shared_ptr<SceneObject>> _childern;

        std::string                     _name;
        scene::Transform                _transform;
        std::shared_ptr<gfx::Texture2D> _texture;
        std::shared_ptr<Cube>           _mesh;

        glm::mat4 _modelMatrix;
        glm::vec3 _position;
        glm::vec3 _rotation;
        glm::vec3 _scale = {1.0f, 1.0f, 1.0f};

        void updateModelMatrix();
};
