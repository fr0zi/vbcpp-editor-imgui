#include "Texture2D.h"

#include <iostream>

namespace gfx
{

Texture2D::Texture2D( std::shared_ptr<Image> image )
{
    std::cout << "Texture Constructor: Creating from Image\n";
    create(image);
}

Texture2D::Texture2D( std::string filename )
{
    std::cout << "Texture Constructor: Creating from file name\n";

    _image = loadImage( filename );

    if (_image)
        create(_image);
}

Texture2D::~Texture2D()
{
    std::cout << "Texture Destructor: " << _id << '\n';

    glDeleteTextures( 1, &_id);
}

void Texture2D::bind()
{
    glBindTexture(GL_TEXTURE_2D, _id);
}

void Texture2D::release()
{
    glBindTexture(GL_TEXTURE_2D, 0);
}

const GLuint& Texture2D::getID()
{
    return _id;
}

const std::shared_ptr<Image> Texture2D::getImage() const
{
    return _image;
}


std::shared_ptr<Image> Texture2D::loadImage( std::string filename )
{
    return std::shared_ptr<Image>( new Image( filename ) );
}

void Texture2D::create( std::shared_ptr<gfx::Image> image )
{
    //GLuint _id;
    glGenTextures( 1, &_id );

    glBindTexture( GL_TEXTURE_2D, _id );
    // set the texture wrapping/filtering options (on the currently bound texture object)
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER );	
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

    glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB, image->getWidth(), image->getHeight(), 0, GL_RGB, GL_UNSIGNED_BYTE, image->getData() );
    glGenerateMipmap( GL_TEXTURE_2D );
}

} // namespace