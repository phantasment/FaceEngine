#include "FaceEngine/Math/Matrix3f.h"

FaceEngine::Matrix3f::Matrix3f(const float& m11, const float& m12, const float& m13, const float& m21, const float& m22, const float& m23, const float& m31, const float& m32, const float& m33)
{
    M11 = m11;
    M12 = m12;
    M13 = m13;
    M21 = m21;
    M22 = m22;
    M23 = m23;
    M31 = m31;
    M32 = m32;
    M33 = m33;
}

float FaceEngine::Matrix3f::GetDeterminant()
{
    return (M11 * ((M22 * M33) - (M23 * M32))) - (M12 * ((M21 * M33) - (M23 * M31))) + (M13 * ((M21 * M32) - (M31 * M22)));
}

const std::vector<float> FaceEngine::Matrix3f::ToArray() const noexcept
{
    return {M11, M12, M13, M21, M22, M23, M31, M32, M33};
}