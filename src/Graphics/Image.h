#ifndef IMAGE_H
#define IMAGE_H

#include <string>
#include <memory>

namespace gfx
{

class Image
{
    public:
        // Default constructor
        Image(const std::string filename);

        // Copy constructor
        Image(const Image& other)
        {
            _data = other._data;
        }

        // Move constructor
        Image(Image&& other) noexcept
        {
            
        }

        ~Image() noexcept;

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

#endif // IMAGE_H