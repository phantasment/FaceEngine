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

        glBufferData(GL_ARRAY_BUFFER, 240, nullptr, GL_DYNAMIC_DRAW);
        GLuint indices[6];
        indices[0] = 0;
        indices[1] = 1;
        indices[2] = 2;
        indices[3] = 2;
        indices[4] = 3;
        indices[5] = 0;
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 60, (void*)0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 60, (void*)(2 * sizeof(float)));
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 60, (void*)(4 * sizeof(float)));
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, 60, (void*)(6 * sizeof(float)));
        glEnableVertexAttribArray(3);
        glVertexAttribPointer(4, 2, GL_FLOAT, GL_FALSE, 60, (void*)(7 * sizeof(float)));
        glEnableVertexAttribArray(4);
        glVertexAttribPointer(5, 2, GL_FLOAT, GL_FALSE, 60, (void*)(9 * sizeof(float)));
        glEnableVertexAttribArray(5);
        glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, 60, (void*)(11 * sizeof(float)));
        glEnableVertexAttribArray(6);
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
        
        float* vertexData = new float[60];
        vertexData[0] = -0.5f;
        vertexData[1] = 0.5f;
        vertexData[15] = 0.5f;
        vertexData[16] = 0.5f;
        vertexData[30] = 0.5f;
        vertexData[31] = -0.5f;
        vertexData[45] = -0.5f;
        vertexData[46] = -0.5f;

        for (const __BatchJob& job : jobs)
        {
            vertexData[2] = (int)job.Rect.Width;
            vertexData[3] = (int)job.Rect.Height;
            vertexData[4] = (int)job.Rect.X;
            vertexData[5] = (int)job.Rect.Y;
            vertexData[6] = job.Rotation;
            vertexData[7] = job.RotationOrigin.X;
            vertexData[8] = job.RotationOrigin.Y;
            vertexData[9] = (int)job.Source.GetLeft();
            vertexData[10] = (int)job.Source.GetTop();
            vertexData[11] = job._Colour.GetR();
            vertexData[12] = job._Colour.GetB();
            vertexData[13] = job._Colour.GetG();
            vertexData[14] = job._Colour.GetA();

            vertexData[17] = (int)job.Rect.Width;
            vertexData[18] = (int)job.Rect.Height;
            vertexData[19] = (int)job.Rect.X;
            vertexData[20] = (int)job.Rect.Y;
            vertexData[21] = job.Rotation;
            vertexData[22] = job.RotationOrigin.X;
            vertexData[23] = job.RotationOrigin.Y;
            vertexData[24] = (int)job.Source.GetRight();
            vertexData[25] = (int)job.Source.GetTop();
            vertexData[26] = job._Colour.GetR();
            vertexData[27] = job._Colour.GetB();
            vertexData[28] = job._Colour.GetG();
            vertexData[29] = job._Colour.GetA();

            vertexData[32] = (int)job.Rect.Width;
            vertexData[33] = (int)job.Rect.Height;
            vertexData[34] = (int)job.Rect.X;
            vertexData[35] = (int)job.Rect.Y;
            vertexData[36] = job.Rotation;
            vertexData[37] = job.RotationOrigin.X;
            vertexData[38] = job.RotationOrigin.Y;
            vertexData[39] = (int)job.Source.GetRight();
            vertexData[40] = (int)job.Source.GetBottom();
            vertexData[41] = job._Colour.GetR();
            vertexData[42] = job._Colour.GetB();
            vertexData[43] = job._Colour.GetG();
            vertexData[44] = job._Colour.GetA();

            vertexData[47] = (int)job.Rect.Width;
            vertexData[48] = (int)job.Rect.Height;
            vertexData[49] = (int)job.Rect.X;
            vertexData[50] = (int)job.Rect.Y;
            vertexData[51] = job.Rotation;
            vertexData[52] = job.RotationOrigin.X;
            vertexData[53] = job.RotationOrigin.Y;
            vertexData[54] = (int)job.Source.GetLeft();
            vertexData[55] = (int)job.Source.GetBottom();
            vertexData[56] = job._Colour.GetR();
            vertexData[57] = job._Colour.GetB();
            vertexData[58] = job._Colour.GetG();
            vertexData[59] = job._Colour.GetA();

            glBufferSubData(GL_ARRAY_BUFFER, 0, 60 * sizeof(float), vertexData);
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
            Vector2f(tex->GetWidth() / 2.0f, tex->GetHeight() / 2.0f),
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
            Vector2f(tex->GetWidth() / 2.0f, tex->GetHeight() / 2.0f),
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
            Vector2f(tex->GetWidth() / 2.0f, tex->GetHeight() / 2.0f),
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
            Vector2f(tex->GetWidth() / 2.0f, tex->GetHeight() / 2.0f),
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
            Vector2f(tex->GetWidth() / 2.0f, tex->GetHeight() / 2.0f),
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
            Vector2f(tex->GetWidth() / 2.0f, tex->GetHeight() / 2.0f),
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
            Vector2f(rect.Width / 2.0f, rect.Height / 2.0f),
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
            Vector2f(rect.Width / 2.0f, rect.Height / 2.0f),
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
            Vector2f(rect.Width / 2.0f, rect.Height / 2.0f),
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
            Vector2f(rect.Width / 2.0f, rect.Height / 2.0f),
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
            Vector2f(rect.Width / 2.0f, rect.Height / 2.0f),
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
            Vector2f(rect.Width / 2.0f, rect.Height / 2.0f),
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
                    Vector2f(tex->GetWidth() / 2.0f, tex->GetHeight() / 2.0f),
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
                    Vector2f(tex->GetWidth() / 2.0f, tex->GetHeight() / 2.0f),
                    FaceEngine::Rectanglef(0.0f, 0.0f, tex->GetHeight(), tex->GetHeight()),
                    col
                };
                jobs.push_back(std::move(job));
            }

            textPos.X += fontChar->GetAdvance() - fontChar->GetBearingX();
        }
    }

    void SpriteBatcher::DrawString(TextureFont* font, const std::string& text, const Vector2f& pos, const Colour& col, const float scale)
    {
        if (!hasBegun)
        {
            throw Exception::FromMessage("FaceEngine::SpriteBatcher::DrawString", "Invalid state.");
        }
        else if (jobs.size() >= MAX_JOBS)
        {
            throw Exception::FromMessage("FaceEngine::SpriteBatcher::Draw", "Max jobs reached.");
        }

        if (text.length() == 0)
        {
            return;
        }

        FaceEngine::Vector2f textPos(pos);

        // First Glyph

        const FontChar* firstGlyph = font->GetFontChar(text[0]);
        const int ascender = font->MeasureString("M").Y * scale;

        if (firstGlyph->HasTexture())
        {
            Texture2D* tex = firstGlyph->GetTexture();

            __BatchJob job
            {
                tex,
                FaceEngine::Rectanglef(textPos.X, pos.Y - ((firstGlyph->GetBearingY() * scale) - ascender), tex->GetWidth() * scale, tex->GetHeight() * scale),
                0.0f,
                Vector2f(tex->GetWidth() / 2.0f, tex->GetHeight() / 2.0f),
                FaceEngine::Rectanglef(0.0f, 0.0f, tex->GetWidth(), tex->GetHeight()),
                col
            };
            
            jobs.push_back(std::move(job));

            textPos.X += (tex->GetWidth() + (firstGlyph->GetAdvance() - (firstGlyph->GetBearingX() + tex->GetWidth()))) * scale;
        }
        else
        {
            textPos.X += firstGlyph->GetAdvance() * scale;
        }

        // Other Glyphs
        
        for (int i = 1; i < text.length() ; ++i)
        {
            const FontChar* glyph = font->GetFontChar(text[i]);
            
            if (glyph->GetTexture() != nullptr)
            {
                Texture2D* tex = glyph->GetTexture();

                __BatchJob job
                {
                    tex,
                    FaceEngine::Rectanglef(textPos.X + (glyph->GetBearingX() * scale), pos.Y - ((glyph->GetBearingY() * scale) - ascender), tex->GetWidth() * scale, tex->GetHeight() * scale),
                    0.0f,
                    Vector2f(tex->GetWidth() / 2.0f, tex->GetHeight() / 2.0f),
                    FaceEngine::Rectanglef(0.0f, 0.0f, glyph->GetTexture()->GetWidth(), glyph->GetTexture()->GetHeight()),
                    col
                };

                jobs.push_back(std::move(job));
            }
            
            textPos.X += glyph->GetAdvance() * scale;
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
        "layout (location = 4) in vec2 rotationOrigin;\n"
        "layout (location = 5) in vec2 texCoord;\n"
        "layout (location = 6) in vec4 texColour;\n"
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