#include "FaceEngine/Shader.h"

namespace FaceEngine
{
    void Shader::Dispose() noexcept
    {
        if (program != 0)
        {
            glDeleteProgram(program);
            program = 0;
        }
    }

    Shader* Shader::CreateShader(ResourceManager* rm, const std::string& vertexShader, const std::string& fragmentShader)
    {
        int success;

        GLuint vs = glCreateShader(GL_VERTEX_SHADER);
        const GLchar* vss = vertexShader.c_str();
        glShaderSource(vs, 1, &vss, 0);
        glCompileShader(vs);
        glGetShaderiv(vs, GL_COMPILE_STATUS, &success);

        if (!success)
        {
            glDeleteShader(vs);
            throw Exception::FromMessage("FaceEngine::Shader::CreateShader", "Couldn't compile vertex shader.");
        }

        GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
        const GLchar* fss = fragmentShader.c_str();
        glShaderSource(fs, 1, &fss, 0);
        glCompileShader(fs);
        glGetShaderiv(fs, GL_COMPILE_STATUS, &success);

        if (!success)
        {
            glDeleteShader(vs);
            glDeleteShader(fs);
            throw Exception::FromMessage("FaceEngine::Shader::CreateShader", "Couldn't compile fragment shader.");
        }

        GLuint program = glCreateProgram();
        glAttachShader(program, vs);
        glAttachShader(program, fs);
        glLinkProgram(program);
        glDeleteShader(vs);
        glDeleteShader(fs);
        glGetProgramiv(program, GL_LINK_STATUS, &success);

        if (!success)
        {
            glDeleteProgram(program);
            throw Exception::FromMessage("FaceEngine::Shader::CreateShader", "Couldn't link shader program.");
        }

        Shader* shader = new Shader(program);
        rm->AddResource(shader);
        return shader;
    }
}