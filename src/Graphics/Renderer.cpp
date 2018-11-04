#include "Renderer.h"
#include "LoadShader.h"

#include <iostream>

namespace gfx
{
    Renderer::Renderer()
        : _clearColor(glm::vec4(0.7f, 0.7f, 0.9f, 1.0f))
    {
        std::cout << "Renderer: Constructor\n";
        shaderID = ShaderLoader::loadShader("Data/shader.vert", "Data/shader.frag");
        AABBoxShaderID = ShaderLoader::loadShader("Data/AABBox.vert", "Data/AABBox.frag");

        glEnable(GL_CULL_FACE);
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);

        //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }

    Renderer::~Renderer()
    {
        std::cout << "Renderer: Destructor\n";
    }
    
    void Renderer::render(std::list<SceneObject*>& root)
    {
        clearScreen();

        

        glUseProgram(shaderID);
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

                // Get uniforms location
        unsigned int transformLoc = glGetUniformLocation(shaderID, "transform");


        if (!_activeCamera)
        {
            std::cout << "Error: No camera has been set!\n";
            return;
        }


        for (auto obj : root)
        {
            Mesh* mesh = nullptr;
            Texture2D* texture = nullptr;
            gfx::RenderComponent* renderComponent = obj->getRenderComponent();

            //if (renderComponent)
            //{
                if (renderComponent->getTexture())
                {
                    texture = renderComponent->getTexture().get();
                }

                if (obj->getRenderComponent()->getMesh())
                {
                    mesh = obj->getRenderComponent()->getMesh().get();
                }
            //}

            if (mesh)
            {
                if (texture)
                    texture->bind();

                glm::mat4 MVP = _activeCamera->getProjectionMatrix() * _activeCamera->getViewMatrix() * obj->getModelMatrix();            

                // Ustawiamy matryce obiektu, potem zmienić na MVP
                glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(MVP));

                glBindVertexArray(mesh->getVAO());

                glDrawElements(GL_TRIANGLES, mesh->getIndexCount(), GL_UNSIGNED_INT, 0);

                if (texture)
                    texture->release();

                glBindVertexArray(0);
            }
        }

        // Rendering AABBox
            
        glUseProgram(AABBoxShaderID);
        transformLoc = glGetUniformLocation(AABBoxShaderID, "transform");
        for (auto obj : root)
        {
            bool drawAABBOX = true;
            if (obj->getDrawAABBox())
            {
                //glEnable(GL_POLYGON_OFFSET_FILL);
                //glPolygonOffset(1, 0);
                glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

                AABBox* aabbox = &obj->getAABBox();
                glm::mat4 MVP = _activeCamera->getProjectionMatrix() * _activeCamera->getViewMatrix() * obj->getModelMatrix();            

                glLineWidth(5.0f);
                glEnable(GL_ALIASED_LINE_WIDTH_RANGE);
                // Ustawiamy matryce obiektu, potem zmienić na MVP
                glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(MVP));

                glBindVertexArray(aabbox->getVAO());

                //glDrawElements(GL_LINES, aabbox->getIndexCount(), GL_UNSIGNED_INT, 0);
                glDrawElements(GL_LINE_LOOP, 4, GL_UNSIGNED_INT, 0);
                glDrawElements(GL_LINE_LOOP, 4, GL_UNSIGNED_INT, (GLvoid*)(4*sizeof(unsigned int)));
                glDrawElements(GL_LINES, 8, GL_UNSIGNED_INT, (GLvoid*)(8*sizeof(unsigned int)));
                glBindVertexArray(0);
            }
        }


    }
    
    void Renderer::setCamera(CameraStatic* camera)
    {
        _activeCamera = camera;
    }

    void Renderer::setClearColor(const glm::vec4 color)
    {
        _clearColor = color;
    }

    void Renderer::clearScreen()
    {
        glClearColor(_clearColor[0], _clearColor[1], _clearColor[2], _clearColor[3]);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

} // namespace