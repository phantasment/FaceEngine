#ifndef FACEENGINE_RESOLUTION_H_
#define FACEENGINE_RESOLUTION_H_

#include <cstdint>
#include <iostream>

namespace FaceEngine
{
    class Resolution
    {
    private:
        std::uint16_t width;
        std::uint16_t height;
    public:
        inline Resolution() : Resolution(0, 0) { }
        
        inline Resolution(const std::uint16_t w, const std::uint16_t h) noexcept
        {
            width = w;
            height = h;
        }

        inline Resolution(const Resolution& res) noexcept
        {
            width = res.width;
            height = res.height;
        }

        inline std::uint16_t GetWidth() const noexcept
        {
            return width;
        }

        inline std::uint16_t GetHeight() const noexcept
        {
            return height;
        }

        inline Resolution& operator=(const Resolution& res)
        {
            width = res.width;
            height = res.height;
            return *this;
        }
    };
}

std::ostream& operator<<(std::ostream& os, const FaceEngine::Resolution& r) noexcept;

#endif