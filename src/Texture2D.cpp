#include "FaceEngine/Texture2D.h"

namespace FaceEngine
{
    void Texture2D::Dispose() noexcept
    {
        if (handle != 0)
        {
            glDeleteTextures(1, &handle);
            handle = 0;
        }
    }

    Texture2D* Texture2D::CreateTexture2D(ResourceManager* rm, const std::uint32_t w, const std::uint32_t h, std::uint8_t* data)
    {
        if (w < 1 || h < 1)
        {
            throw Exception::FromMessage("FaceEngine::Texture2D::CreateTexture2D", "Width and height of texture must be more than 0.");
        }

        GLuint texId;
        glGenTextures(1, &texId);
        glBindTexture(GL_TEXTURE_2D, texId);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glPixelStorei(GL_PACK_ALIGNMENT, 4);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        Texture2D* tex = new Texture2D(texId, w, h);
        rm->TrackResource(tex);
        return tex;
    }
}