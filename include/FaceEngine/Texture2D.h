#ifndef FACEENGINE_TEXTURE2D_H_
#define FACEENGINE_TEXTURE2D_H_

#include <cstdint>

#include "FaceEngine/OGL.h"
#include "FaceEngine/Resource.h"
#include "FaceEngine/ResourceManager.h"
#include "FaceEngine/Exception.h"

namespace FaceEngine
{
    class Texture2D : public Resource
    {
    private:
        GLuint handle;
        std::uint32_t width, height;
    
        inline Texture2D(GLuint t, const std::uint32_t w, const std::uint32_t h) noexcept
        {
            handle = t;
            width = w;
            height = h;
        }
    public:
        inline const bool IsDisposed() noexcept override
        {
            return handle == 0;
        }

        void Dispose() noexcept override;

        inline const GLuint GetHandle() const noexcept
        {
            return handle;
        }

        inline const std::uint32_t GetWidth() const noexcept
        {
            return width;
        }

        inline const std::uint32_t GetHeight() const noexcept
        {
            return height;
        }

        static Texture2D* CreateTexture2D(ResourceManager*, const std::uint32_t, const std::uint32_t, std::uint8_t*);
    };
}

#endif