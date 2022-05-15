#ifndef FACEENGINE_MATH_MATRIX3F_H_
#define FACEENGINE_MATH_MATRIX3F_H_

#include "FaceEngine/Math/Matrix.h"
#include "FaceEngine/Math/Vector2.h"
#include "FaceEngine/Math/Vector3.h"

namespace FaceEngine
{
    class Matrix3f : public FaceEngine::Matrix
    {
    public:
        float M11, M12, M13, M21, M22, M23, M31, M32, M33;

        Matrix3f();
        Matrix3f(const float& m11, const float& m12, const float& m13, const float& m21, const float& m22, const float& m23, const float& m31, const float& m32, const float& m33);

        float GetDeterminant();

        void Transform(Vector2<float>& vector) const noexcept;
        void Transform(Vector3f& vector) const noexcept;

        const std::vector<float> ToArray() const noexcept override;
    };
}

FaceEngine::Vector2f operator *(const FaceEngine::Matrix3f& matrix, const FaceEngine::Vector2f& vector) noexcept;
FaceEngine::Vector3f operator *(const FaceEngine::Matrix3f& matrix, const FaceEngine::Vector3f& vector) noexcept;

#endif