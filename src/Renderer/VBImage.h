#ifndef VBIMAGE_H
#define VBIMAGE_H

#include <string>
#include <memory>

namespace gfx
{

class VBImage
{
    public:
        // Default constructor
        VBImage(const std::string filename);

        // Copy constructor
        VBImage(const VBImage& other)
        {
            _data = other._data;
        }

        // Move constructor
        VBImage(VBImage&& other) noexcept
        {
            
        }

        ~VBImage() noexcept;

        unsigned char* getData() const;

        const int getWidth() const;

        const int getHeight() const;

        const int getChannelCount() const;

    private:
        std::string _name;
        int _width, _height, _channelCount;

        unsigned char* _data;

        void loadData();

};

} // namespace

#endif // VBIMAGE_H