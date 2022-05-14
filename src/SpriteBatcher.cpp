#include "FaceEngine/SpriteBatcher.h"

namespace FaceEngine
{
    SpriteBatcher::SpriteBatcher(Window* w, ResourceManager* rm, Shader* s) noexcept
    {
        win = w;
        resMan = rm;
        shader = s;
        disposed = false;

        glGenVertexArrays(1, &vao);
        glGenBuffers(1, &vbo);
        glGenBuffers(1, &ebo);

        glBindVertexArray(vao);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

        glBufferData(GL_ARRAY_BUFFER, 128, nullptr, GL_DYNAMIC_DRAW);
        GLuint indices[6];
        indices[0] = 0;
        indices[1] = 1;
        indices[2] = 2;
        indices[3] = 2;
        indices[4] = 3;
        indices[5] = 0;
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(2 * sizeof(float)));
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
        glEnableVertexAttribArray(2);
    }

    void SpriteBatcher::Draw(Texture2D* tex)
    {
        if (jobs.size() >= MAX_JOBS)
        {
            throw Exception::FromMessage("FaceEngine::SpriteBatcher::Draw", "Max jobs reached.");
        }

        BatchJob job
        {
            tex,
            Rectanglef(0.0f, 0.0f, tex->Width(), tex->Height()),
            Rectanglef(0.0f, 0.0f, tex->Width(), tex->Height()),
            Colour::White
        };
        jobs.push_back(std::move(job));
    }

    void SpriteBatcher::Draw(Texture2D* tex, const Colour& col)
    {
        if (jobs.size() >= MAX_JOBS)
        {
            throw Exception::FromMessage("FaceEngine::SpriteBatcher::Draw", "Max jobs reached.");
        }

        BatchJob job
        {
            tex,
            Rectanglef(0.0f, 0.0f, tex->Width(), tex->Height()),
            Rectanglef(0.0f, 0.0f, tex->Width(), tex->Height()),
            col
        };
        jobs.push_back(std::move(job));
    }

    void SpriteBatcher::Draw(Texture2D* tex, const Vector2f& vec2)
    {
        if (jobs.size() >= MAX_JOBS)
        {
            throw Exception::FromMessage("FaceEngine::SpriteBatcher::Draw", "Max jobs reached.");
        }

        BatchJob job
        {
            tex,
            Rectanglef(vec2.X, vec2.Y, tex->Width(), tex->Height()),
            Rectanglef(0.0f, 0.0f, tex->Width(), tex->Height()),
            Colour::White
        };
        jobs.push_back(std::move(job));
    }

    void SpriteBatcher::Draw(Texture2D* tex, const Vector2f& vec2, const Colour& col)
    {
        if (jobs.size() >= MAX_JOBS)
        {
            throw Exception::FromMessage("FaceEngine::SpriteBatcher::Draw", "Max jobs reached.");
        }

        BatchJob job
        {
            tex,
            Rectanglef(vec2.X, vec2.Y, tex->Width(), tex->Height()),
            Rectanglef(0.0f, 0.0f, tex->Width(), tex->Height()),
            col
        };
        jobs.push_back(std::move(job));
    }

    void SpriteBatcher::Draw(Texture2D* tex, const Rectanglef& rect)
    {
        if (jobs.size() >= MAX_JOBS)
        {
            throw Exception::FromMessage("FaceEngine::SpriteBatcher::Draw", "Max jobs reached.");
        }

        BatchJob job
        {
            tex,
            rect,
            Rectanglef(0.0f, 0.0f, tex->Width(), tex->Height()),
            Colour::White
        };
        jobs.push_back(std::move(job));
    }

    void SpriteBatcher::Flush() noexcept
    {
        if (jobs.empty())
        {
            return;
        }

        glBindVertexArray(vao);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        glActiveTexture(GL_TEXTURE0);

        shader->SetActive();
        const Resolution& resolution = win->CurrentResolution();
        shader->SetUniform("projection", Matrix4f::CreateOrthographic(resolution.Width(), resolution.Height(), 0.0f, 1.0f));
        shader->SetUniform("transform", Matrix4f::Identity);
        
        float* vertexData = new float[32];

        for (BatchJob& job : jobs)
        {
            vertexData[0] = job.Rect.GetLeft();
            vertexData[1] = job.Rect.GetTop();
            vertexData[2] = job.Colour.GetR();
            vertexData[3] = job.Colour.GetG();
            vertexData[4] = job.Colour.GetB();
            vertexData[5] = job.Colour.GetA();
            vertexData[6] = job.Source.GetLeft();
            vertexData[7] = job.Source.GetTop();

            vertexData[8] = job.Rect.GetRight();
            vertexData[9] = job.Rect.GetTop();
            vertexData[10] = job.Colour.GetR();
            vertexData[11] = job.Colour.GetG();
            vertexData[12] = job.Colour.GetB();
            vertexData[13] = job.Colour.GetA();
            vertexData[14] = job.Source.GetRight();
            vertexData[15] = job.Source.GetTop();

            vertexData[16] = job.Rect.GetRight();
            vertexData[17] = job.Rect.GetBottom();
            vertexData[18] = job.Colour.GetR();
            vertexData[19] = job.Colour.GetG();
            vertexData[20] = job.Colour.GetB();
            vertexData[21] = job.Colour.GetA();
            vertexData[22] = job.Source.GetRight();
            vertexData[23] = job.Source.GetBottom();

            vertexData[24] = job.Rect.GetLeft();
            vertexData[25] = job.Rect.GetBottom();
            vertexData[26] = job.Colour.GetR();
            vertexData[27] = job.Colour.GetG();
            vertexData[28] = job.Colour.GetB();
            vertexData[29] = job.Colour.GetA();
            vertexData[30] = job.Source.GetLeft();
            vertexData[31] = job.Source.GetBottom();

            glBufferSubData(GL_ARRAY_BUFFER, 0, 32 * sizeof(float), vertexData);
            shader->SetUniform("textureSize", Vector2f(job.Texture->Width(), job.Texture->Height()));
            glBindTexture(GL_TEXTURE_2D, job.Texture->Handle());
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        }

        delete[] vertexData;
        jobs.clear();
    }

    SpriteBatcher* SpriteBatcher::CreateSpriteBatcher(ResourceManager* rm, Window* win)
    {
        Shader* shader = Shader::CreateShader(rm,
        // vertex shader
        "#version 330 core\n"

        "layout (location = 0) in vec2 vert;\n"
        "layout (location = 1) in vec4 colour;\n"
        "layout (location = 2) in vec2 textureCoord;\n"

        "out vec4 fragColour;\n"
        "out vec2 fragTextureCoord;\n"

        "uniform mat4 projection;\n"
        "uniform mat4 transform;\n"

        "void main()\n"
        "{\n"
            "gl_Position = projection * transform * vec4(vert.x, vert.y, 0.0, 1.0);\n"
            "fragColour = colour;\n"
            "fragTextureCoord = textureCoord;\n"
        "}",
        // fragment shader
        "#version 330 core\n"

        "out vec4 fragmentColour;\n"

        "in vec4 fragColour;\n"
        "in vec2 fragTextureCoord;\n"

        "uniform vec2 textureSize;\n"
        "uniform sampler2D textureSampler;\n"

        "void main()\n"
        "{\n"
            "fragmentColour = texture(textureSampler, vec2(fragTextureCoord.x / textureSize.x, 1.0 - (fragTextureCoord.y / textureSize.y))) * fragColour;\n"
            "if (fragmentColour.w == 0.0) { discard; }\n"
        "}");
        
        SpriteBatcher* result = new SpriteBatcher(win, rm, shader);
        rm->TrackResource(result);
        return result;
    }
}