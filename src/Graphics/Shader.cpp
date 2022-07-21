#include "FaceEngine/Graphics/Shader.h"

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

    void Shader::SetUniform(const std::string& name, const Vector2f& vec2)
    {
        GLint l = glGetUniformLocation(program, name.c_str());

        if (l == -1)
        {
            throw Exception::FromMessage("FaceEngine::Shader::SetUniform", "Invalid uniform name.");
        }

        glUniform2fv(l, 1, &vec2.ToArray()[0]);
    }

    void Shader::SetUniform(const std::string& name, const Matrix4f& mat4)
    {
        GLint l = glGetUniformLocation(program, name.c_str());

        if (l == -1)
        {
            throw Exception::FromMessage("FaceEngine::Shader::SetUniform", "Invalid uniform name.");
        }

        glUniformMatrix4fv(l, 1, GL_FALSE, &mat4.ToArray()[0]);
    }

    Shader* Shader::CreateShader(ResourceManager* rm, const std::string& vertexShader, const std::string& fragmentShader)
    {
        int success;
        const char* infoLog = new char[1024];

        GLuint vs = glCreateShader(GL_VERTEX_SHADER);
        const GLchar* vss = vertexShader.c_str();
        glShaderSource(vs, 1, &vss, 0);
        glCompileShader(vs);
        glGetShaderiv(vs, GL_COMPILE_STATUS, &success);

        if (!success)
        {
            glGetShaderInfoLog(vs, 1024, NULL, (GLchar*)infoLog);
            std::string log(infoLog);
            delete[] infoLog;
            glDeleteShader(vs);
            throw Exception::FromMessage("FaceEngine::Shader::CreateShader", "Couldn't compile vertex shader: " + log);
        }

        GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
        const GLchar* fss = fragmentShader.c_str();
        glShaderSource(fs, 1, &fss, 0);
        glCompileShader(fs);
        glGetShaderiv(fs, GL_COMPILE_STATUS, &success);

        if (!success)
        {
            glGetShaderInfoLog(fs, 1024, NULL, (GLchar*)infoLog);
            std::string log(infoLog);
            delete[] infoLog;
            glDeleteShader(vs);
            glDeleteShader(fs);
            throw Exception::FromMessage("FaceEngine::Shader::CreateShader", "Couldn't compile fragment shader: " + log);
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
            glGetProgramInfoLog(program, 1024, NULL, (GLchar*)infoLog);
            std::string log(infoLog);
            delete[] infoLog;
            glDeleteProgram(program);
            throw Exception::FromMessage("FaceEngine::Shader::CreateShader", "Couldn't link shader program: " + log);
        }

        delete[] infoLog;
        Shader* shader = new Shader(program);
        rm->TrackResource(shader);
        return shader;
    }
}