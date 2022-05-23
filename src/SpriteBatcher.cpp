#include "FaceEngine/SpriteBatcher.h"

namespace FaceEngine
{
    SpriteBatcher::SpriteBatcher(Window* w, ResourceManager* rm, Shader* s) noexcept
    {
        win = w;
        resMan = rm;
        shader = s;
        disposed = false;
        hasBegun = false;

        glGenVertexArrays(1, &vao);
        glGenBuffers(1, &vbo);
        glGenBuffers(1, &ebo);

        glBindVertexArray(vao);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

        glBufferData(GL_ARRAY_BUFFER, 208, nullptr, GL_DYNAMIC_DRAW);
        GLuint indices[6];
        indices[0] = 0;
        indices[1] = 1;
        indices[2] = 2;
        indices[3] = 2;
        indices[4] = 3;
        indices[5] = 0;
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 52, (void*)0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 52, (void*)8);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 52, (void*)16);
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, 52, (void*)24);
        glEnableVertexAttribArray(3);
        glVertexAttribPointer(4, 2, GL_FLOAT, GL_FALSE, 52, (void*)28);
        glEnableVertexAttribArray(4);
        glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, 52, (void*)36);
        glEnableVertexAttribArray(5);
    }

    void SpriteBatcher::Begin()
    {
        if (hasBegun)
        {
            throw Exception::FromMessage("FaceEngine::SpriteBatcher::Begin", "Invalid state.");
        }

        hasBegun = true;
        transform = Matrix4f::Identity;
    }

    void SpriteBatcher::Begin(const Vector2f& translation)
    {
        if (hasBegun)
        {
            throw Exception::FromMessage("FaceEngine::SpriteBatcher::Begin", "Invalid state.");
        }

        hasBegun = true;
        transform = Matrix4f::CreateTranslation(translation.X, translation.Y, 0.0f);
    }

    void SpriteBatcher::Begin(const Matrix4f& mat4)
    {
        if (hasBegun)
        {
            throw Exception::FromMessage("FaceEngine::SpriteBatcher::Begin", "Invalid state.");
        }

        hasBegun = true;
        transform = mat4;
    }

    void SpriteBatcher::End()
    {
        if (!hasBegun)
        {
            throw Exception::FromMessage("FaceEngine::SpriteBatcher::Begin", "Invalid state.");
        }

        hasBegun = false;

        if (jobs.empty())
        {
            return;
        }

        glBindVertexArray(vao);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        glActiveTexture(GL_TEXTURE0);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        shader->SetActive();
        const Resolution& resolution = win->GetResolution();
        shader->SetUniform("projection", Matrix4f::CreateOrthographic(resolution.GetWidth(), resolution.GetHeight(), 0.0f, 1.0f));
        shader->SetUniform("windowSize", Vector2f(resolution.GetWidth(), resolution.GetHeight()));
        shader->SetUniform("transform", transform);
        
        float* vertexData = new float[52];
        vertexData[0] = -0.5f;
        vertexData[1] = 0.5f;
        vertexData[13] = 0.5f;
        vertexData[14] = 0.5f;
        vertexData[26] = 0.5f;
        vertexData[27] = -0.5f;
        vertexData[39] = -0.5f;
        vertexData[40] = -0.5f;

        for (const __BatchJob& job : jobs)
        {
            vertexData[2] = (int)job.Rect.Width;
            vertexData[3] = (int)job.Rect.Height;
            vertexData[4] = (int)job.Rect.X;
            vertexData[5] = (int)job.Rect.Y;
            vertexData[6] = job.Rotation;
            vertexData[7] = (int)job.Source.GetLeft();
            vertexData[8] = (int)job.Source.GetTop();
            vertexData[9] = job.Colour.GetR();
            vertexData[10] = job.Colour.GetB();
            vertexData[11] = job.Colour.GetG();
            vertexData[12] = job.Colour.GetA();

            vertexData[15] = (int)job.Rect.Width;
            vertexData[16] = (int)job.Rect.Height;
            vertexData[17] = (int)job.Rect.X;
            vertexData[18] = (int)job.Rect.Y;
            vertexData[19] = job.Rotation;
            vertexData[20] = (int)job.Source.GetRight();
            vertexData[21] = (int)job.Source.GetTop();
            vertexData[22] = job.Colour.GetR();
            vertexData[23] = job.Colour.GetB();
            vertexData[24] = job.Colour.GetG();
            vertexData[25] = job.Colour.GetA();

            vertexData[28] = (int)job.Rect.Width;
            vertexData[29] = (int)job.Rect.Height;
            vertexData[30] = (int)job.Rect.X;
            vertexData[31] = (int)job.Rect.Y;
            vertexData[32] = job.Rotation;
            vertexData[33] = (int)job.Source.GetRight();
            vertexData[34] = (int)job.Source.GetBottom();
            vertexData[35] = job.Colour.GetR();
            vertexData[36] = job.Colour.GetB();
            vertexData[37] = job.Colour.GetG();
            vertexData[38] = job.Colour.GetA();

            vertexData[41] = (int)job.Rect.Width;
            vertexData[42] = (int)job.Rect.Height;
            vertexData[43] = (int)job.Rect.X;
            vertexData[44] = (int)job.Rect.Y;
            vertexData[45] = job.Rotation;
            vertexData[46] = (int)job.Source.GetLeft();
            vertexData[47] = (int)job.Source.GetBottom();
            vertexData[48] = job.Colour.GetR();
            vertexData[49] = job.Colour.GetB();
            vertexData[50] = job.Colour.GetG();
            vertexData[51] = job.Colour.GetA();

            glBufferSubData(GL_ARRAY_BUFFER, 0, 52 * sizeof(float), vertexData);
            glBindTexture(GL_TEXTURE_2D, job.Texture->GetHandle());
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        }

        delete[] vertexData;
        jobs.clear();
    }

    void SpriteBatcher::Draw(Texture2D* tex)
    {
        if (!hasBegun)
        {
            throw Exception::FromMessage("FaceEngine::SpriteBatcher::Draw", "Invalid state.");
        }
        else if (jobs.size() >= MAX_JOBS)
        {
            throw Exception::FromMessage("FaceEngine::SpriteBatcher::Draw", "Max jobs reached.");
        }

        __BatchJob job
        {
            tex,
            Rectanglef(0.0f, 0.0f, tex->GetWidth(), tex->GetHeight()),
            0.0f,
            Rectanglef(0.0f, 0.0f, tex->GetWidth(), tex->GetHeight()),
            Colour::White
        };
        jobs.push_back(std::move(job));
    }

    void SpriteBatcher::Draw(Texture2D* tex, const Colour& col)
    {
        if (!hasBegun)
        {
            throw Exception::FromMessage("FaceEngine::SpriteBatcher::Draw", "Invalid state.");
        }
        else if (jobs.size() >= MAX_JOBS)
        {
            throw Exception::FromMessage("FaceEngine::SpriteBatcher::Draw", "Max jobs reached.");
        }

        __BatchJob job
        {
            tex,
            Rectanglef(0.0f, 0.0f, tex->GetWidth(), tex->GetHeight()),
            0.0f,
            Rectanglef(0.0f, 0.0f, tex->GetWidth(), tex->GetHeight()),
            col
        };
        jobs.push_back(std::move(job));
    }

    void SpriteBatcher::Draw(Texture2D* tex, float rotation, const Colour& col)
    {
        if (!hasBegun)
        {
            throw Exception::FromMessage("FaceEngine::SpriteBatcher::Draw", "Invalid state.");
        }
        else if (jobs.size() >= MAX_JOBS)
        {
            throw Exception::FromMessage("FaceEngine::SpriteBatcher::Draw", "Max jobs reached.");
        }

        __BatchJob job
        {
            tex,
            Rectanglef(0.0f, 0.0f, tex->GetWidth(), tex->GetHeight()),
            rotation,
            Rectanglef(0.0f, 0.0f, tex->GetWidth(), tex->GetHeight()),
            col
        };
        jobs.push_back(std::move(job));
    }

    void SpriteBatcher::Draw(Texture2D* tex, const Vector2f& vec2)
    {
        if (!hasBegun)
        {
            throw Exception::FromMessage("FaceEngine::SpriteBatcher::Draw", "Invalid state.");
        }
        else if (jobs.size() >= MAX_JOBS)
        {
            throw Exception::FromMessage("FaceEngine::SpriteBatcher::Draw", "Max jobs reached.");
        }

        __BatchJob job
        {
            tex,
            Rectanglef(vec2.X, vec2.Y, tex->GetWidth(), tex->GetHeight()),
            0.0f,
            Rectanglef(0.0f, 0.0f, tex->GetWidth(), tex->GetHeight()),
            Colour::White
        };
        jobs.push_back(std::move(job));
    }

    void SpriteBatcher::Draw(Texture2D* tex, const Vector2f& vec2, const Colour& col)
    {
        if (!hasBegun)
        {
            throw Exception::FromMessage("FaceEngine::SpriteBatcher::Draw", "Invalid state.");
        }
        else if (jobs.size() >= MAX_JOBS)
        {
            throw Exception::FromMessage("FaceEngine::SpriteBatcher::Draw", "Max jobs reached.");
        }

        __BatchJob job
        {
            tex,
            Rectanglef(vec2.X, vec2.Y, tex->GetWidth(), tex->GetHeight()),
            0.0f,
            Rectanglef(0.0f, 0.0f, tex->GetWidth(), tex->GetHeight()),
            col
        };
        jobs.push_back(std::move(job));
    }

    void SpriteBatcher::Draw(Texture2D* tex, const Vector2f& vec2, float rotation, const Colour& col)
    {
        if (!hasBegun)
        {
            throw Exception::FromMessage("FaceEngine::SpriteBatcher::Draw", "Invalid state.");
        }
        else if (jobs.size() >= MAX_JOBS)
        {
            throw Exception::FromMessage("FaceEngine::SpriteBatcher::Draw", "Max jobs reached.");
        }

        __BatchJob job
        {
            tex,
            Rectanglef(vec2.X, vec2.Y, tex->GetWidth(), tex->GetHeight()),
            rotation,
            Rectanglef(0.0f, 0.0f, tex->GetWidth(), tex->GetHeight()),
            col
        };
        jobs.push_back(std::move(job));
    }

    void SpriteBatcher::Draw(Texture2D* tex, const Rectanglef& rect)
    {
        if (!hasBegun)
        {
            throw Exception::FromMessage("FaceEngine::SpriteBatcher::Draw", "Invalid state.");
        }
        else if (jobs.size() >= MAX_JOBS)
        {
            throw Exception::FromMessage("FaceEngine::SpriteBatcher::Draw", "Max jobs reached.");
        }

        __BatchJob job
        {
            tex,
            rect,
            0.0f,
            Rectanglef(0.0f, 0.0f, tex->GetWidth(), tex->GetHeight()),
            Colour::White
        };
        jobs.push_back(std::move(job));
    }

    void SpriteBatcher::Draw(Texture2D* tex, const Rectanglef& rect, const Colour& col)
    {
        if (!hasBegun)
        {
            throw Exception::FromMessage("FaceEngine::SpriteBatcher::Draw", "Invalid state.");
        }
        else if (jobs.size() >= MAX_JOBS)
        {
            throw Exception::FromMessage("FaceEngine::SpriteBatcher::Draw", "Max jobs reached.");
        }

        __BatchJob job
        {
            tex,
            rect,
            0.0f,
            Rectanglef(0.0f, 0.0f, tex->GetWidth(), tex->GetHeight()),
            col
        };
        jobs.push_back(std::move(job));
    }

    void SpriteBatcher::Draw(Texture2D* tex, const Rectanglef& rect, float rotation, const Colour& col)
    {
        if (!hasBegun)
        {
            throw Exception::FromMessage("FaceEngine::SpriteBatcher::Draw", "Invalid state.");
        }
        else if (jobs.size() >= MAX_JOBS)
        {
            throw Exception::FromMessage("FaceEngine::SpriteBatcher::Draw", "Max jobs reached.");
        }

        __BatchJob job
        {
            tex,
            rect,
            rotation,
            Rectanglef(0.0f, 0.0f, tex->GetWidth(), tex->GetHeight()),
            col
        };
        jobs.push_back(std::move(job));
    }

    void SpriteBatcher::Draw(Texture2D* tex, const Rectanglef& rect, const Rectanglef& src)
    {
        if (!hasBegun)
        {
            throw Exception::FromMessage("FaceEngine::SpriteBatcher::Draw", "Invalid state.");
        }
        else if (jobs.size() >= MAX_JOBS)
        {
            throw Exception::FromMessage("FaceEngine::SpriteBatcher::Draw", "Max jobs reached.");
        }

        __BatchJob job
        {
            tex,
            rect,
            0.0f,
            src,
            Colour::White
        };
        jobs.push_back(std::move(job));
    }

    void SpriteBatcher::Draw(Texture2D* tex, const Rectanglef& rect, const Rectanglef& src, const Colour& col)
    {
        if (!hasBegun)
        {
            throw Exception::FromMessage("FaceEngine::SpriteBatcher::Draw", "Invalid state.");
        }
        else if (jobs.size() >= MAX_JOBS)
        {
            throw Exception::FromMessage("FaceEngine::SpriteBatcher::Draw", "Max jobs reached.");
        }

        __BatchJob job
        {
            tex,
            rect,
            0.0f,
            src,
            col
        };
        jobs.push_back(std::move(job));
    }

    void SpriteBatcher::Draw(Texture2D* tex, const Rectanglef& rect, const Rectanglef& src, float rotation, const Colour& col)
    {
        if (!hasBegun)
        {
            throw Exception::FromMessage("FaceEngine::SpriteBatcher::Draw", "Invalid state.");
        }
        else if (jobs.size() >= MAX_JOBS)
        {
            throw Exception::FromMessage("FaceEngine::SpriteBatcher::Draw", "Max jobs reached.");
        }

        __BatchJob job
        {
            tex,
            rect,
            rotation,
            src,
            col
        };
        jobs.push_back(std::move(job));
    }

    void SpriteBatcher::DrawString(TextureFont* font, const std::string& text, const Vector2f& pos)
    {
        if (!hasBegun)
        {
            throw Exception::FromMessage("FaceEngine::SpriteBatcher::Draw", "Invalid state.");
        }
        else if (jobs.size() >= MAX_JOBS)
        {
            throw Exception::FromMessage("FaceEngine::SpriteBatcher::Draw", "Max jobs reached.");
        }

        Vector2f textPos(pos);

        for (std::uint8_t c : text)
        {
            const FaceEngine::FontChar* fontChar = font->GetFontChar((std::uint32_t)c);

            if (fontChar->HasTexture())
            {
                Texture2D* tex = fontChar->GetTexture();

                __BatchJob job
                {
                    fontChar->GetTexture(),
                    FaceEngine::Rectanglef(textPos.X, textPos.Y - fontChar->GetBearingY() + (font->GetAscender() / 64), tex->GetHeight(), tex->GetHeight()),
                    0.0f,
                    FaceEngine::Rectanglef(0.0f, 0.0f, tex->GetHeight(), tex->GetHeight()),
                    Colour::White
                };
                jobs.push_back(std::move(job));
            }

            textPos.X += fontChar->GetAdvance() - fontChar->GetBearingX();
        }
    }

    void SpriteBatcher::DrawString(TextureFont* font, const std::string& text, const Vector2f& pos, const Colour& col)
    {
        if (!hasBegun)
        {
            throw Exception::FromMessage("FaceEngine::SpriteBatcher::Draw", "Invalid state.");
        }
        else if (jobs.size() >= MAX_JOBS)
        {
            throw Exception::FromMessage("FaceEngine::SpriteBatcher::Draw", "Max jobs reached.");
        }

        Vector2f textPos(pos);

        for (std::uint8_t c : text)
        {
            const FaceEngine::FontChar* fontChar = font->GetFontChar((std::uint32_t)c);

            if (fontChar->HasTexture())
            {
                Texture2D* tex = fontChar->GetTexture();

                __BatchJob job
                {
                    fontChar->GetTexture(),
                    FaceEngine::Rectanglef(textPos.X, textPos.Y - fontChar->GetBearingY() + (font->GetAscender() / 64), tex->GetHeight(), tex->GetHeight()),
                    0.0f,
                    FaceEngine::Rectanglef(0.0f, 0.0f, tex->GetHeight(), tex->GetHeight()),
                    col
                };
                jobs.push_back(std::move(job));
            }

            textPos.X += fontChar->GetAdvance() - fontChar->GetBearingX();
        }
    }

    SpriteBatcher* SpriteBatcher::CreateSpriteBatcher(ResourceManager* rm, Window* win)
    {
        Shader* shader = Shader::CreateShader(rm,
        // vertex shader
        "#version 330 core\n"
        "\n"
        "layout (location = 0) in vec2 vert;\n"
        "layout (location = 1) in vec2 scale;\n"
        "layout (location = 2) in vec2 translation;\n"
        "layout (location = 3) in float rotation;\n"
        "layout (location = 4) in vec2 texCoord;\n"
        "layout (location = 5) in vec4 texColour;\n"
        "\n"
        "out vec2 fragTexCoord;\n"
        "out vec4 fragColour;\n"
        "\n"
        "uniform mat4 projection;\n"
        "uniform vec2 windowSize;\n"
        "uniform mat4 transform;\n"
        "\n"
        "mat4 create_translate(float x, float y)\n"
        "{\n"
        "\treturn mat4\n"
        "\t(\n"
        "\t\t1, 0, 0, 0,\n"
        "\t\t0, 1, 0, 0,\n"
        "\t\t0, 0, 1, 0,\n"
        "\t\tx - ((windowSize.x - scale.x) / 2), ((windowSize.y - scale.y) / 2) - y, 0, 1\n"
        "\t);\n"
        "}\n"
        "\n"
        "mat4 create_rotate(float r)\n"
        "{\n"
        "\treturn mat4\n"
        "\t(\n"
        "\t\tcos(r), sin(r), 0, 0,\n"
        "\t\t-sin(r), cos(r),  0, 0,\n"
        "\t\t0,      0,       1, 0,\n"
        "\t\t0,      0,       0, 1\n"
        "\t);\n"
        "}\n"
        "\n"
        "mat4 create_scale(float x, float y)\n"
        "{\n"
        "\treturn mat4\n"
        "\t(\n"
        "\t\tx, 0, 0, 0,\n"
        "\t\t0, y, 0, 0,\n"
        "\t\t0, 0, 1, 0,\n"
        "\t\t0, 0, 0, 1\n"
        "\t);\n"
        "}\n"
        "\n"
        "void main()\n"
        "{\n"
        "\t// translation, rotation, scale\n"
        "\tgl_Position = projection * transform * create_translate(translation.x, translation.y) * create_rotate(rotation) * create_scale(scale.x, scale.y) * vec4(vert.xy, 0.0, 1.0);\n"
        "\tfragTexCoord = texCoord;\n"
        "\tfragColour = texColour;\n"
        "}",
        // fragment shader
        "#version 330 core\n"

        "out vec4 fragmentColour;\n"

        "in vec2 fragTexCoord;\n"
        "in vec4 fragColour;\n"
        
        "uniform sampler2D textureSampler;\n"

        "void main()\n"
        "{\n"
            "ivec2 texSize = textureSize(textureSampler, 0);"
            "fragmentColour = texelFetch(textureSampler, ivec2(floor(fragTexCoord.x), floor(texSize.y - fragTexCoord.y)), 0) * fragColour;"
            "if (fragmentColour.w == 0.0) { discard; }\n"
        "}");
        
        SpriteBatcher* result = new SpriteBatcher(win, rm, shader);
        rm->TrackResource(result);
        return result;
    }
}