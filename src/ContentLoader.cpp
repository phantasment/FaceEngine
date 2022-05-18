#include "FaceEngine/ContentLoader.h"

#include <cstring>
#include <cstdio>
#include <zlib.h>

namespace FaceEngine
{
    std::uint32_t ContentLoader::BytesToInt32(const std::array<std::uint8_t, 4>& bytes) noexcept
    {
        return (std::uint32_t)((0xFF & bytes[0]) << 24) | ((0xFF & bytes[1]) << 16) | ((0xFF & bytes[2]) << 8) | (0xFF & bytes[3]);
    }

    bool ContentLoader::IsValidHeader(const std::uint8_t* header) const noexcept
    {
        return std::memcmp(contentFileHeader.data(), header, 16) == 0;
    }

    Texture2D* ContentLoader::LoadTexture2D(const std::string& path) const
    {
        std::FILE* fp = std::fopen(path.c_str(), "rb");

        if (!fp)
        {
            throw Exception::FromMessage("FaceEngine::ContentLoader::LoadTexture2D", "Couldn't open file for reading.");
        }

        std::uint8_t buffer[16];

        if (std::fread(buffer, 16, 1, fp) != 1 ||
            !IsValidHeader(buffer) ||
            std::fread(buffer, 1, 1, fp) != 1 || buffer[0] != contentFileVersion ||
            std::fread(buffer, 1, 1, fp) != 1 || buffer[0] != TypeTexture2D ||
            std::fread(buffer, 9, 1, fp) != 1)
        {
            std::fclose(fp);
            throw Exception::FromMessage("FaceEngine::ContentLoader::LoadTexture2D", "Invalid content file.");
        }
        
        std::uint32_t width = BytesToInt32({ buffer[0], buffer[1], buffer[2], buffer[3] });
        std::uint32_t height = BytesToInt32({ buffer[4], buffer[5], buffer[6], buffer[7] });
        std::uint8_t compressLevel = buffer[8];

        if (width < 0 || width > 2048 ||
            height < 0 || height > 2048 ||
            compressLevel < 0 || compressLevel > Z_BEST_COMPRESSION)
        {
            std::fclose(fp);
            throw Exception::FromMessage("FaceEngine::ContentLoader::LoadTexture2D", "Invalid content file.");
        }

        std::size_t imageDataSize = width * height * 4;
        std::uint8_t* imageData = new std::uint8_t[imageDataSize];

        if (compressLevel == 0)
        {
            if (std::fread(imageData, imageDataSize, 1, fp) != 1)
            {
                delete[] imageData;
                std::fclose(fp);
                throw Exception::FromMessage("FaceEngine::ContentLoader::LoadTexture2D", "Invalid content file.");
            }
        }
        else
        {
            if (std::fread(buffer, 1, 4, fp) != 4)
            {
                delete[] imageData;
                std::fclose(fp);
                throw Exception::FromMessage("FaceEngine::ContentLoader::LoadTexture2D", "Invalid content file.");
            }

            std::size_t compressedDataSize = BytesToInt32({ buffer[0], buffer[1], buffer[2], buffer[3] });
            std::uint8_t* compressedImageData = new std::uint8_t[compressedDataSize];

            if (std::fread(compressedImageData, 1, compressedDataSize, fp) != compressedDataSize)
            {
                delete[] imageData;
                delete[] compressedImageData;
                std::fclose(fp);
                throw Exception::FromMessage("FaceEngine::ContentLoader::LoadTexture2D", "Invalid content file.");
            }

            z_stream zStream;
            zStream.zalloc = nullptr;
            zStream.zfree = nullptr;
            zStream.opaque = nullptr;
            zStream.avail_in = compressedDataSize;
            zStream.next_in = (Bytef*)compressedImageData;
            zStream.avail_out = imageDataSize;
            zStream.next_out = (Bytef*)imageData;
            inflateInit(&zStream);
            inflate(&zStream, Z_NO_FLUSH);
            inflateEnd(&zStream);
            delete[] compressedImageData;

            if (zStream.total_out != imageDataSize)
            {
                delete[] imageData;
                std::fclose(fp);
                throw Exception::FromMessage("FaceEngine::ContentLoader::LoadTexture2D", "Invalid content file.");
            }
        }

        std::fclose(fp);
        Texture2D* result = Texture2D::CreateTexture2D(resMan, width, height, imageData);
        delete[] imageData;
        return result;
    }

    TextureFont* ContentLoader::LoadTextureFont(const std::string& path) const
    {
        std::FILE* fp = std::fopen(path.c_str(), "rb");

        if (!fp)
        {
            throw Exception::FromMessage("FaceEngine::ContentLoader::LoadTextureFont", "Couldn't open file for reading.");
        }

        std::uint8_t buffer[24];

        if (std::fread(buffer, 16, 1, fp) != 1 ||
            !IsValidHeader(buffer) ||
            std::fread(buffer, 1, 1, fp) != 1 || buffer[0] != contentFileVersion ||
            std::fread(buffer, 1, 1, fp) != 1 || buffer[0] != TypeTextureFont ||
            std::fread(buffer, 20, 1, fp) != 1)
        {
            std::fclose(fp);
            throw Exception::FromMessage("FaceEngine::ContentLoader::LoadTextureFont", "Invalid content file.");
        }

        std::uint32_t size = BytesToInt32({ buffer[0], buffer[1], buffer[2], buffer[3] });
        std::int32_t ascender = BytesToInt32({ buffer[4], buffer[5], buffer[6], buffer[7] });
        std::int32_t descender = BytesToInt32({ buffer[8], buffer[9], buffer[10], buffer[11] });
        std::int32_t lineSpacing = BytesToInt32({ buffer[12], buffer[13], buffer[14], buffer[15] });
        std::uint32_t charCount = BytesToInt32({ buffer[16], buffer[17], buffer[18], buffer[19] });
        std::vector<FontChar> fontChars;
        std::uint8_t* data;
        std::uint8_t* textureData;
        std::uint8_t* compressedData;

        for (std::uint32_t count = 0; count < charCount; ++count)
        {
            if (std::fread(buffer, 24, 1, fp) != 1)
            {
                std::fclose(fp);
                throw Exception::FromMessage("FaceEngine::ContentLoader::LoadTextureFont", "Invalid content file.");
            }

            std::uint32_t charCode = BytesToInt32({ buffer[0], buffer[1], buffer[2], buffer[3] });
            std::int32_t bearingX = BytesToInt32({ buffer[4], buffer[5], buffer[6], buffer[7] });
            std::int32_t bearingY = BytesToInt32({ buffer[8], buffer[9], buffer[10], buffer[11] });
            std::int32_t advance = BytesToInt32({ buffer[12], buffer[13], buffer[14], buffer[15] });
            std::uint32_t width = BytesToInt32({ buffer[16], buffer[17], buffer[18], buffer[19] });
            std::uint32_t height = BytesToInt32({ buffer[20], buffer[21], buffer[22], buffer[23] });
            Texture2D* texture;

            if (width == 0 || height == 0)
            {
                fontChars.emplace_back(charCode, bearingX, bearingY, advance, nullptr);
                continue;
            }

            std::size_t dataSize = width * height;
            std::size_t textureDataSize = dataSize * 4;
            std::uint8_t compressLevel;

            if (std::fread(&compressLevel, 1, 1, fp) != 1)
            {
                std::fclose(fp);
                throw Exception::FromMessage("FaceEngine::ContentLoader::LoadTextureFont", "Invalid content file.");
            }

            if (compressLevel == 0)
            {
                data = new std::uint8_t[dataSize];
                
                if (std::fread(data, dataSize, 1, fp) != 1)
                {
                    delete[] data;
                    std::fclose(fp);
                    throw Exception::FromMessage("FaceEngine::ContentLoader::LoadTextureFont", "Invalid content file.");
                }

                textureData = new std::uint8_t[textureDataSize];
                std::size_t pos = 0;

                for (std::size_t i = 0; i < textureDataSize; i += 4)
                {
                    textureData[i] = 0xFF;
                    textureData[i + 1] = 0xFF;
                    textureData[i + 2] = 0xFF;
                    textureData[i + 3] = data[pos++];
                }

                delete[] data;
                texture = Texture2D::CreateTexture2D(resMan, width, height, textureData);
                delete[] textureData;
            }
            else
            {
                if (std::fread(buffer, 4, 1, fp) != 1)
                {
                    std::fclose(fp);
                    throw Exception::FromMessage("FaceEngine::ContentLoader::LoadTextureFont", "Invalid content file.");
                }

                std::size_t compressedDataSize = BytesToInt32({ buffer[0], buffer[1], buffer[2], buffer[3] });
                compressedData = new std::uint8_t[compressedDataSize];

                if (std::fread(compressedData, compressedDataSize, 1, fp) != 1)
                {
                    delete[] compressedData;
                    std::fclose(fp);
                    throw Exception::FromMessage("FaceEngine::ContentLoader::LoadTextureFont", "Invalid content file.");
                }

                data = new std::uint8_t[dataSize];
                z_stream zStream;
                zStream.zalloc = nullptr;
                zStream.zfree = nullptr;
                zStream.opaque = nullptr;
                zStream.avail_in = compressedDataSize;
                zStream.next_in = (Bytef*)compressedData;
                zStream.avail_out = dataSize;
                zStream.next_out = (Bytef*)data;
                inflateInit(&zStream);
                inflate(&zStream, Z_NO_FLUSH);
                inflateEnd(&zStream);
                delete[] compressedData;
                textureData = new std::uint8_t[textureDataSize];
                std::size_t pos = 0;

                for (std::size_t i = 0; i < textureDataSize; i += 4)
                {
                    textureData[i] = 0xFF;
                    textureData[i + 1] = 0xFF;
                    textureData[i + 2] = 0xFF;
                    textureData[i + 3] = data[pos++];
                }

                delete[] data;
                texture = Texture2D::CreateTexture2D(resMan, width, height, textureData);
                delete[] textureData;
            }

            fontChars.emplace_back(charCode, bearingX, bearingY, advance, texture);
        }

        return TextureFont::CreateTextureFont(resMan, size, ascender, descender, lineSpacing, fontChars);
    }
}