#ifndef FACEENGINE_MATH_MATRIX4F_H_
#define FACEENGINE_MATH_MATRIX4F_H_

#include "FaceEngine/Math/Matrix.h"

namespace FaceEngine
{
    class Matrix4f : public Matrix
    {
    private:
        float data[4][4];
    public:
        Matrix4f();

        Matrix4f& Identity() noexcept;
        Matrix4f& Translation() noexcept;
        Matrix4f& Rotation() noexcept;
        Matrix4f& Scale() noexcept;
        Matrix4f& Ortho() noexcept;

        const std::vector<float> ToArray() const noexcept override;
    };
}

#endif