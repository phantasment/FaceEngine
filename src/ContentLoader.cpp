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

        unsigned char buffer[16];

        if (std::fread(buffer, 16, 1, fp) != 1 ||
            !IsValidHeader(buffer) ||
            std::fread(buffer, 1, 1, fp) != 1 || buffer[0] != contentFileVersion ||
            std::fread(buffer, 1, 1, fp) != 1 || buffer[0] != TypeTexture2D ||
            std::fread(buffer, 9, 1, fp) != 1)
        {
            std::fclose(fp);
            throw Exception::FromMessage("FaceEngine::ContentLoader::LoadTexture2D", "Invalid content file. 1");
        }
        
        std::uint32_t width = BytesToInt32({ buffer[0], buffer[1], buffer[2], buffer[3] });
        std::uint32_t height = BytesToInt32({ buffer[4], buffer[5], buffer[6], buffer[7] });
        std::uint8_t compressLevel = buffer[8];

        if (width < 0 || width > 2048 ||
            height < 0 || height > 2048 ||
            compressLevel < 0 || compressLevel > Z_BEST_COMPRESSION)
        {
            std::fclose(fp);
            throw Exception::FromMessage("FaceEngine::ContentLoader::LoadTexture2D", "Invalid content file. 2");
        }

        std::size_t imageDataSize = width * height * 4;
        std::uint8_t* imageData = new std::uint8_t[imageDataSize];

        if (compressLevel == 0)
        {
            if (std::fread(imageData, imageDataSize, 1, fp) != 1)
            {
                delete[] imageData;
                std::fclose(fp);
                throw Exception::FromMessage("FaceEngine::ContentLoader::LoadTexture2D", "Invalid content file. 3");
            }
        }
        else
        {
            if (std::fread(buffer, 1, 4, fp) != 4)
            {
                delete[] imageData;
                std::fclose(fp);
                throw Exception::FromMessage("FaceEngine::ContentLoader::LoadTexture2D", "Invalid content file. 4");
            }

            std::size_t compressedDataSize = BytesToInt32({ buffer[0], buffer[1], buffer[2], buffer[3] });
            unsigned char* compressedImageData = new unsigned char[compressedDataSize];

            if (std::fread(compressedImageData, 1, compressedDataSize, fp) != compressedDataSize)
            {
                delete[] imageData;
                delete[] compressedImageData;
                std::fclose(fp);
                throw Exception::FromMessage("FaceEngine::ContentLoader::LoadTexture2D", "Invalid content file. 5");
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
                throw Exception::FromMessage("FaceEngine::ContentLoader::LoadTexture2D", "Invalid content file. 6");
            }
        }

        std::fclose(fp);
        Texture2D* result = Texture2D::CreateTexture2D(resMan, width, height, imageData);
        delete[] imageData;
        return result;
    }
}