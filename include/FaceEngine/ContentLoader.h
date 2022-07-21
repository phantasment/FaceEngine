#ifndef FACEENGINE_CONTENTLOADER_H_
#define FACEENGINE_CONTENTLOADER_H_

#include <cstdint>
#include <array>

#include "FaceEngine/ResourceManager.h"
#include "FaceEngine/Graphics/Texture2D.h"
#include "FaceEngine/Graphics/TextureFont.h"

namespace FaceEngine
{
    enum ContentFileType : std::uint8_t
    {
        TypeTexture2D = 1,
        TypeTextureFont = 2
    };

    class ContentLoader : public Resource
    {
        friend class Game;
    private:
        ResourceManager* resMan;

        inline ContentLoader(ResourceManager* rm) noexcept
        {
            resMan = rm;
        }

        static std::uint32_t BytesToInt32(const std::array<std::uint8_t, 4>&) noexcept;

        std::array<std::uint8_t, 16> contentFileHeader = { 'F', 'E', 'C', 'F', 2, 3, 1, 0, 7, 2, 2, 2, 9, 6, 'E', 'W' };
        std::uint8_t contentFileVersion = 1;

        bool IsValidHeader(const std::uint8_t*) const noexcept;
    public:
        /**
         * @brief Loads a Texture2D from a Face Engine content file specified by the path.
         * 
         * @return Texture2D* A pointer to the newly created Texture2D.
         */
        Texture2D* LoadTexture2D(const std::string&) const;

        TextureFont* LoadTextureFont(const std::string&) const;
    };
}

#endif