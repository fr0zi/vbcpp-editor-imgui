#ifndef VERTEX_H
#define VERTEX_H

#include "glm/glm.hpp"

namespace gfx
{

struct Vertex
{
    glm::vec3   position;
    glm::vec3   color;
    glm::vec2   texCoord;
};

} // namespace

#endif // VERTEX_H__