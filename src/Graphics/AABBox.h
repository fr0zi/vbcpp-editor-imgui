#pragma once

#include <vector>
#include <memory>
#include <iostream>

#include "Vertex.h"
#include "glm/glm.hpp"

#include "../Graphics/Vertex.h"
#include "glm/glm.hpp"

// GLFW, GLEW
#include "GL/glew.h"

// Include GLU header with GLFW
#define GLFW_INCLUDE_GLU
#include "GLFW/glfw3.h"

#include "Mesh.h"

class AABBox
{
    public:
        AABBox(Mesh* mesh = nullptr);

        ~AABBox();

        const unsigned int getVertexCount() const;

        const unsigned int getIndexCount() const;

        const gfx::Vertex* getVerticesData() const;

        const unsigned int* getIndicesData() const;

        const GLuint& getVAO() const;

        void createBufferObjects();

    private:
        GLuint _VAO;
        GLuint _VBO;
        GLuint _EBO;

        std::vector<gfx::Vertex>    _vertices;
        std::vector<unsigned int>   _indices;
};