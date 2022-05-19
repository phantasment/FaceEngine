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

        /**
         * @brief Begins a sprite batch with the specified translation.
         * 
         */
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

        /**
         * @brief Draws a texture.
         * The texture will be drawn at 0,0 using the default colour and the default source rectangle.
         * 
         * This function creates a batch job. To complete it, call Flush().
         */
        void Draw(Texture2D*);

        /**
         * @brief Draws a texture.
         * The texture will be drawn at 0,0 using the specified colour and the default source rectangle.
         * 
         * This function creates a batch job. To complete it, call Flush().
         */
        void Draw(Texture2D*, const Colour&);

        /**
         * @brief Draws a texture.
         * The texture will be drawn at the specified position using the default colour and the default source rectangle.
         * 
         * This function creates a batch job. To complete it, call Flush().
         */
        void Draw(Texture2D*, const Vector2f&);

        /**
         * @brief Draws a texture.
         * The texture will be drawn at the specified position using the specified colour and the default source rectangle.
         * 
         * This function creates a batch job. To complete it, call Flush().
         */
        void Draw(Texture2D*, const Vector2f&, const Colour&);

        /**
         * @brief Draws a texture.
         * The texture will be drawn using the specified rectangle using the default colour and the default source rectangle.
         * 
         * This function creates a batch job. To complete it, call Flush().
         */
        void Draw(Texture2D*, const Rectanglef&);

        /**
         * @brief Draws a texture.
         * The texture will be drawn using the specified rectangle using the specified colour and the default source rectangle.
         * 
         * This function creates a batch job. To complete it, call Flush().
         */
        void Draw(Texture2D*, const Rectanglef&, const Colour&);

        /**
         * @brief Draws a texture.
         * The texture will be drawn using the specified rectangle using the default colour and the specified source rectangle.
         * 
         * This function creates a batch job. To complete it, call Flush().
         */
        void Draw(Texture2D*, const Rectanglef&, const Rectanglef&);

        void Draw(Texture2D*, const Rectanglef&, const Rectanglef&, float);

        /**
         * @brief Draws a texture.
         * The texture will be drawn using the specified rectangle using the specified colour and the specified source rectangle.
         * 
         * This function creates a batch job. To complete it, call Flush().
         */
        void Draw(Texture2D*, const Rectanglef&, const Rectanglef&, const Colour&);

        /**
         * @brief Constructs a SpriteBatcher object.
         * @return SpriteBatcher* A pointer to the newly created object.
         */
        static SpriteBatcher* CreateSpriteBatcher(ResourceManager*, Window*);
    };
}

#endif