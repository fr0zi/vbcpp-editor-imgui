#ifndef CUBE_H
#define CUBE_H

#include <vector>
#include <memory>
#include <iostream>

#include "Vertex.h"
#include "glm/glm.hpp"

class Cube
{
    public:
        Cube()
        {
            std::cout << "Cube: Constructor\n";
            _vertices.resize(8);

            _vertices[0].position = glm::vec3( 0.5f, 0.5f,0.5f);
            _vertices[0].color = glm::vec3( 1.0f, 1.0f, 1.0f);
            _vertices[0].texCoord = glm::vec2(1,0);

            _vertices[1].position = glm::vec3( 0.5f,-0.5f,0.5f);
            _vertices[0].color = glm::vec3( 1.0f, 1.0f, 1.0f);
            _vertices[1].texCoord = glm::vec2(1,1);

            _vertices[2].position = glm::vec3(-0.5f,-0.5f,0.5f);
            _vertices[0].color = glm::vec3( 1.0f, 1.0f, 1.0f);
            _vertices[2].texCoord = glm::vec2(0,1);

            _vertices[3].position = glm::vec3(-0.5f, 0.5f,0.5f);
            _vertices[0].color = glm::vec3( 1.0f, 1.0f, 1.0f);
            _vertices[3].texCoord = glm::vec2(0,0);


            _vertices[4].position = glm::vec3( 0.5f, 0.5f,-0.5f);
            _vertices[0].color = glm::vec3( 1.0f, 1.0f, 1.0f);
            _vertices[4].texCoord = glm::vec2(0,0);

            _vertices[5].position = glm::vec3( 0.5f,-0.5f,-0.5f);
            _vertices[0].color = glm::vec3( 1.0f, 1.0f, 1.0f);
            _vertices[5].texCoord = glm::vec2(0,1);

            _vertices[6].position = glm::vec3(-0.5f,-0.5f,-0.5f);
            _vertices[0].color = glm::vec3( 1.0f, 1.0f, 1.0f);
            _vertices[6].texCoord = glm::vec2(1,1);

            _vertices[7].position = glm::vec3(-0.5f, 0.5f,-0.5f);
            _vertices[0].color = glm::vec3( 1.0f, 1.0f, 1.0f);
            _vertices[7].texCoord = glm::vec2(1,0);

            _indices.resize(36);

            _indices[0] = 0;
            _indices[1] = 3;
            _indices[2] = 2;
            _indices[3] = 0;
            _indices[4] = 2;
            _indices[5] = 1;
            _indices[6] = 7;
            _indices[7] = 4;
            _indices[8] = 6;
            _indices[9] = 4;
            _indices[10] = 5;
            _indices[11] = 6;
            _indices[12] = 4;
            _indices[13] = 0;
            _indices[14] = 5;
            _indices[15] = 0;
            _indices[16] = 1;
            _indices[17] = 5;
            _indices[18] = 3;
            _indices[19] = 7;
            _indices[20] = 2;
            _indices[21] = 7;
            _indices[22] = 6;
            _indices[23] = 2;
            _indices[24] = 4;
            _indices[25] = 7;
            _indices[26] = 0;
            _indices[27] = 7;
            _indices[28] = 3;
            _indices[29] = 0;
            _indices[30] = 1;
            _indices[31] = 2;
            _indices[32] = 5;
            _indices[33] = 2;
            _indices[34] = 6;
            _indices[35] = 5;

            createBufferObjects();
        }

        ~Cube()
        {
            std::cout << "Cube: Destructor\n";

            glDeleteVertexArrays(1, &_VAO);
            glDeleteBuffers(1, &_VBO);
        }

        unsigned int getVertexCount()
        {
            return _vertices.size();
        }

        unsigned int getIndexCount()
        {
            return _indices.size();
        }

        gfx::Vertex* getVerticesData()
        {
            return _vertices.data();
        }

        unsigned int* getIndicesData()
        {
            return _indices.data();
        }

        GLuint& getVAO()
        {
            return _VAO;
        }

        void createBufferObjects()
        {
            glGenVertexArrays(1, &_VAO);

            glGenBuffers(1, &_VBO);

            glGenBuffers(1, &_EBO);

            // Vertex data
            glBindVertexArray(_VAO);
            glBindBuffer(GL_ARRAY_BUFFER, _VBO);
            glBufferData(GL_ARRAY_BUFFER, _vertices.size() * sizeof(gfx::Vertex), _vertices.data(), GL_STATIC_DRAW);

            // Index data
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _EBO);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, _indices.size() * sizeof(unsigned int), _indices.data(), GL_STATIC_DRAW);

    
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
            glEnableVertexAttribArray(0);

            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
            glEnableVertexAttribArray(1);

            glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
            glEnableVertexAttribArray(2);

            glBindVertexArray(0);
        }

    private:
        GLuint _VAO;
        GLuint _VBO;
        GLuint _EBO;

        std::vector<gfx::Vertex>    _vertices;
        std::vector<unsigned int>   _indices;
};

#endif // CUBE_H