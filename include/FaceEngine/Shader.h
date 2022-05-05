#ifndef FACEENGINE_SHADER_H_
#define FACEENGINE_SHADER_H_

#include <string>

#include "FaceEngine/OGL.h"
#include "FaceEngine/Resource.h"
#include "FaceEngine/Exception.h"
#include "FaceEngine/ResourceManager.h"

namespace FaceEngine
{
    class Shader : public Resource
    {
    private:
        GLuint program;

        inline Shader(const GLuint p) noexcept
        {
            program = p;
        }
    public:
        inline const bool IsDisposed() noexcept override
        {
            return program == 0;
        }

        void Dispose() noexcept override;

        static Shader* CreateShader(ResourceManager*, const std::string&, const std::string&);
    };
}

#endif