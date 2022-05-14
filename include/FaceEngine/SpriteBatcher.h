#ifndef FACEENGINE_SPRITEBATCHER_H_
#define FACEENGINE_SPRITEBATCHER_H_

#include <vector>

#include "FaceEngine/Exception.h"
#include "FaceEngine/Window.h"
#include "FaceEngine/Resource.h"
#include "FaceEngine/ResourceManager.h"
#include "FaceEngine/Math/Rectangle.h"
#include "FaceEngine/Colour.h"
#include "FaceEngine/Shader.h"
#include "FaceEngine/Texture2D.h"

#define MAX_JOBS 4194304UL

namespace FaceEngine
{
    struct BatchJob
    {
        inline BatchJob()
        {
            Colour = Colour::White;
        }

        inline BatchJob(Texture2D* t)
        {
            Texture = t;
            Rect.Width = t->Width();
            Rect.Height = t->Height();
            Source.Width = t->Width();
            Source.Height = t->Height();
            Colour = Colour::White;
        }

        Texture2D* Texture;
        Rectangle<float> Rect;
        Rectangle<float> Source;
        Colour Colour;
    };

    class SpriteBatcher : public Resource
    {
    private:
        bool disposed;
        Window* win;
        ResourceManager* resMan;
        Shader* shader;
        GLuint vao, vbo, ebo;
        std::vector<BatchJob> jobs;

        SpriteBatcher(Window*, ResourceManager*, Shader*) noexcept;
    public:
        inline const bool IsDisposed() noexcept override { return disposed; }
        inline void Dispose() noexcept override { resMan->DisposeResource(shader); disposed = true; }

        void Draw(Texture2D*);

        void Flush() noexcept;

        static SpriteBatcher* CreateSpriteBatcher(ResourceManager*, Window*);
    };
}

#endif