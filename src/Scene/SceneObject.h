#pragma once

#include <string>
#include <list>
#include <memory>

#include "Transform.h"
#include "../Graphics/Texture2D.h"
#include "../Graphics/Mesh.h"
#include "../Graphics/RenderComponent.h"

class SceneObject;

using SceneObjectList = std::list<std::shared_ptr<SceneObject>>;




class SceneObject : public std::enable_shared_from_this<SceneObject>
{
    public:
        SceneObject(SceneObject* parent = nullptr, std::string name = "SceneObject");
        virtual ~SceneObject();

        void setRenderComponent(std::shared_ptr<gfx::RenderComponent> mesh);

        std::shared_ptr<gfx::RenderComponent> getRenderComponent();

        void setName(std::string name);

        const std::string getName() const;

        void setParent(std::shared_ptr<SceneObject> parent);

        std::shared_ptr<SceneObject> getParent();

        void addChild(std::shared_ptr<SceneObject> child);

        void removeChild(std::shared_ptr<SceneObject> child);

        const int getChildCount() const noexcept;

        SceneObject* getChildAt(unsigned int index);

        // Transform
        void setPosition( const glm::vec3 position );

        void setRotation( const glm::vec3 rotation );

        void setScale( const glm::vec3 scale );

        glm::vec3& getPositionRef();

        glm::vec3& getRotationRef();

        glm::vec3& getScaleRef();

        const glm::mat4& getModelMatrix(); 

    protected:
        std::weak_ptr<SceneObject>    _parent;
        SceneObjectList               _children;

        std::string                     _name;
        std::shared_ptr<gfx::RenderComponent> _renderComponent;

        glm::mat4 _modelMatrix;
        glm::vec3 _position;
        glm::vec3 _rotation;
        glm::vec3 _scale = {1.0f, 1.0f, 1.0f};

        void updateModelMatrix();
};
