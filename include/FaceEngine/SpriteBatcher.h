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
#include "FaceEngine/TextureFont.h"

#define MAX_JOBS 4194304UL

namespace FaceEngine
{
    struct BatchJob
    {
        Texture2D* Texture;
        Rectanglef Rect;
        float Rotation;
        Rectanglef Source;
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
        Matrix4f transform;
        bool hasBegun;

        SpriteBatcher(Window*, ResourceManager*, Shader*) noexcept;
    public:
        inline bool IsDisposed() noexcept override { return disposed; }
        inline void Dispose() noexcept override { resMan->DisposeResource(shader); disposed = true; }
    
        /**
         * @brief Begins a sprite batch with an identity transform.
         */
        void Begin();

        void Begin(const Vector2f&);

        /**
         * @brief Begins a sprite batch with the specified transform.
         * 
         */
        void Begin(const Matrix4f&);

        /**
         * @brief Ends a sprite batch. All sprite jobs will be drawn and removed from the batch.
         */
        void End();

        void Draw(Texture2D*);
        void Draw(Texture2D*, const Colour&);
        void Draw(Texture2D*, float, const Colour&);
        void Draw(Texture2D*, const Vector2f&);
        void Draw(Texture2D*, const Vector2f&, const Colour&);
        void Draw(Texture2D*, const Vector2f&, float, const Colour&);
        void Draw(Texture2D*, const Rectanglef&);
        void Draw(Texture2D*, const Rectanglef&, const Colour&);
        void Draw(Texture2D*, const Rectanglef&, float, const Colour&);
        void Draw(Texture2D*, const Rectanglef&, const Rectanglef&);
        void Draw(Texture2D*, const Rectanglef&, const Rectanglef&, const Colour&);
        void Draw(Texture2D*, const Rectanglef&, const Rectanglef&, float, const Colour&);

        void DrawString(TextureFont*, const std::string&, const Vector2f&);
        void DrawString(TextureFont*, const std::string&, const Vector2f&, const Colour&);

        /**
         * @brief Constructs a SpriteBatcher object.
         * @return SpriteBatcher* A pointer to the newly created object.
         */
        static SpriteBatcher* CreateSpriteBatcher(ResourceManager*, Window*);
    };
}

#endif