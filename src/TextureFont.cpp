#include "FaceEngine/TextureFont.h"

namespace FaceEngine
{
    void TextureFont::Dispose() noexcept
    {
        for (const FontChar& fontChar : fontChars)
        {
            resMan->DisposeResource(fontChar.GetTexture());
        }

        fontChars.clear();
    }

    const FontChar* TextureFont::GetFontChar(std::uint32_t asciiCode) const
    {
        for (const FontChar& fontChar : fontChars)
        {
            if (fontChar.GetCharCode() == asciiCode)
            {
                return &fontChar;
            }
        }

        throw Exception::FromMessage("FaceEngine::TextureFont::GetFontChar", "No font character exists for that ASCII code.");
    }

    TextureFont* TextureFont::CreateTextureFont(ResourceManager* rm, std::uint32_t size, std::int32_t ascender, std::int32_t descender, std::int32_t lineSpacing, const std::vector<FontChar>& fontChars)
    {
        TextureFont* font = new TextureFont(rm, size, ascender, descender, lineSpacing, fontChars);
        rm->TrackResource(font);
        return font;
    }
}