#include "VBImage.h"

#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

namespace gfx
{

VBImage::VBImage(const std::string filename)
    : _name(filename), _width(0), _height(0)
{
    std::cout << "VBImage Constructor: Loading Image data\n";
    loadData();
}

VBImage::~VBImage()
{
    std::cout << "VBImage Destructor: Releasing Image data\n";
    stbi_image_free(_data);
}

unsigned char* VBImage::getData() const
{
    return _data;
}

const int VBImage::getWidth() const
{
    return _width;
}

const int VBImage::getHeight() const
{
    return _height;
}

const int VBImage::getChannelCount() const
{
    return _channelCount;
}

void VBImage::loadData()
{
    _data = stbi_load(_name.c_str(), &_width, &_height, &_channelCount, 0);

    if(!_data)
    {
        std::cout << "Could not load file: " << _name << "! Texture may be invalid!\n";
    }
}

} //namespace