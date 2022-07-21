#include "FaceEngine/Graphics/TextureFont.h"

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

    Vector2f TextureFont::MeasureString(const std::string& text) const
    {
        Vector2f result(0, 0);
        int yMax = 0;
        int yMin = 0;

        if (text.length() == 0)
        {
            return result;
        }

        const FontChar* firstGlyph = GetFontChar(text[0]);

        if (firstGlyph->HasTexture())
        {
            Texture2D* texture = firstGlyph->GetTexture();
            result.X = firstGlyph->GetBearingX() < 0 ? texture->GetWidth() + std::abs(firstGlyph->GetBearingX()) : texture->GetWidth();
            yMax = firstGlyph->GetBearingY();
            yMin = firstGlyph->GetBearingY() - texture->GetHeight();

            if (text.length() > 1)
            {
                result.X += firstGlyph->GetAdvance() - (texture->GetWidth() + std::max(firstGlyph->GetBearingX(), 0));
            }
        }
        else
        {
            result.X += firstGlyph->GetAdvance();
        }

        for (std::size_t i = 1; i < text.length() - 1; ++i)
        {
            const FontChar* glyph = GetFontChar(text[i]);
            result.X += glyph->GetAdvance();

            if (glyph->HasTexture())
            {

                yMax = std::max(glyph->GetBearingY(), yMax);
                yMin = std::min(glyph->GetBearingY() - (std::int32_t)glyph->GetTexture()->GetHeight(), yMin);
            }
        }

        if (text.length() > 1)
        {
            const FontChar* lastGlyph = GetFontChar(text[text.length() - 1]);

            if (lastGlyph->HasTexture())
            {
                Texture2D* texture = lastGlyph->GetTexture();
                result.X += lastGlyph->GetBearingX() + texture->GetWidth();
                yMax = std::max(lastGlyph->GetBearingY(), yMax);
                yMin = std::min(lastGlyph->GetBearingY() - (std::int32_t)texture->GetHeight(), yMin);
            }
            else
            {
                result.X += lastGlyph->GetAdvance();
            }
        }

        result.Y = yMax + std::abs(yMin);
        return result;
    }

    TextureFont* TextureFont::CreateTextureFont(ResourceManager* rm, std::uint32_t size, std::int32_t ascender, std::int32_t descender, std::int32_t lineSpacing, const std::vector<FontChar>& fontChars)
    {
        TextureFont* font = new TextureFont(rm, size, ascender, descender, lineSpacing, fontChars);
        rm->TrackResource(font);
        return font;
    }
}