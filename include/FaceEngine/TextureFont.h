#ifndef FACEENGINE_TEXTUREFONT_H_
#define FACEENGINE_TEXTUREFONT_H_

#include <cstdint>
#include <vector>

#include "FaceEngine/Resource.h"
#include "FaceEngine/ResourceManager.h"
#include "FaceEngine/Texture2D.h"

namespace FaceEngine
{
    class FontChar
    {
    private:
        std::uint32_t charCode;
        std::int32_t bearingX, bearingY;
        std::int32_t advance;
        Texture2D* texture;
    public:
        inline FontChar(std::uint32_t c, std::int32_t x, std::int32_t y, std::int32_t a, Texture2D* t) noexcept
        {
            charCode = c;
            bearingX = x;
            bearingY = y;
            advance = a;
            texture = t;
        }

        inline std::uint32_t GetCharCode() const noexcept { return charCode; }

        inline std::int32_t GetBearingX() const noexcept { return bearingX; }

        inline std::int32_t GetBearingY() const noexcept { return bearingY; }

        inline std::int32_t GetAdvance() const noexcept { return advance; }

        inline Texture2D* GetTexture() const noexcept { return texture; }

        inline bool HasTexture() const noexcept { return texture != nullptr; }
    };

    class TextureFont : public Resource
    {
    private:
        ResourceManager* resMan;

        std::uint32_t size;
        std::int32_t ascender;
        std::int32_t descender;
        std::int32_t lineSpacing;
        std::vector<FontChar> fontChars;
    public:
        inline TextureFont(ResourceManager* r, std::uint32_t s, std::int32_t a, std::int32_t d, std::int32_t l, const std::vector<FontChar>& c)
        {
            resMan = r;
            size = s;
            ascender = a;
            descender = d;
            lineSpacing = l;
            fontChars = c;
        }

        inline bool IsDisposed() noexcept override
        {
            return fontChars.size() == 0;
        }

        void Dispose() noexcept override;

        inline std::uint32_t GetSize() const noexcept { return size; }

        inline std::int32_t GetAscender() const noexcept { return ascender; }

        inline std::int32_t GetDescender() const noexcept { return descender; }

        inline std::int32_t GetLineSpacing() const noexcept { return lineSpacing; }

        inline const std::vector<FontChar>& GetFontChars() const noexcept { return fontChars; }

        const FontChar* GetFontChar(std::uint32_t) const;

        static TextureFont* CreateTextureFont(ResourceManager*, std::uint32_t, std::int32_t, std::int32_t, std::int32_t, const std::vector<FontChar>&);
    };
}

#endif