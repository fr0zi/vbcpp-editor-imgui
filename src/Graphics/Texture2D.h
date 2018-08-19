#pragma once

#include <string>

#include "GL/glew.h"

// Include GLU header with GLFW
#define GLFW_INCLUDE_GLU
#include "GLFW/glfw3.h"

#include "Image.h"

namespace gfx
{

class Texture2D
{
    public:
        Texture2D( std::shared_ptr<gfx::Image> image );
        Texture2D( std::string filename );
        ~Texture2D();

        void bind();
        void release();

        const GLuint& getID();

    private:
        GLuint _id;

        std::shared_ptr<Image> loadImage( std::string filename );
        void create( std::shared_ptr<Image> image );
};

} // namespace