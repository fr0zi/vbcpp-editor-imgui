#include "Image.h"

#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

namespace gfx
{

Image::Image(const std::string filename)
    : _name(filename), _width(0), _height(0)
{
    std::cout << "Image Constructor: Loading Image data\n";
    loadData();
}

Image::~Image()
{
    std::cout << "Image Destructor: Releasing Image data\n";
    stbi_image_free(_data);
}

unsigned char* Image::getData() const
{
    return _data;
}

const int Image::getWidth() const
{
    return _width;
}

const int Image::getHeight() const
{
    return _height;
}

const int Image::getChannelCount() const
{
    return _channelCount;
}

const std::string Image::getName() const
{
    return _name;
}

void Image::loadData()
{
    _data = stbi_load(_name.c_str(), &_width, &_height, &_channelCount, 0);

    if(!_data)
    {
        std::cout << "Could not load file: " << _name << "! Texture may be invalid!\n";
    }
}

} //namespace