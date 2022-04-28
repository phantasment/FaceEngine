#ifndef FACEENGINE_MATH_MATRIX3F_H_
#define FACEENGINE_MATH_MATRIX3F_H_

#include "FaceEngine/Math/Matrix.h"

namespace FaceEngine
{
    class Matrix3f : public FaceEngine::Matrix
    {
    public:
        float M11, M12, M13, M21, M22, M23, M31, M32, M33;

        Matrix3f();
        Matrix3f(const float& m11, const float& m12, const float& m13, const float& m21, const float& m22, const float& m23, const float& m31, const float& m32, const float& m33);

        float GetDeterminant();

        const std::vector<float> ToArray() const noexcept override;
    };
}

#endif