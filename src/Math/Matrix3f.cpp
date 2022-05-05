#include "FaceEngine/Math/Matrix3f.h"

namespace FaceEngine
{
    Matrix3f::Matrix3f(const float& m11, const float& m12, const float& m13, const float& m21, const float& m22, const float& m23, const float& m31, const float& m32, const float& m33)
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

    float Matrix3f::GetDeterminant()
    {
        return (M11 * ((M22 * M33) - (M23 * M32))) - (M12 * ((M21 * M33) - (M23 * M31))) + (M13 * ((M21 * M32) - (M31 * M22)));
    }

    void Matrix3f::Transform(Vector2f& vector) const noexcept
    {
        float oldX = vector.X;
        
        vector.X = vector.X * M11 + vector.Y * M12 + M13;
        vector.Y = oldX * M21 + vector.Y * M22 + M23;
    }

    void Matrix3f::Transform(Vector3f& vector) const noexcept
    {
        float oldX = vector.X;
        float oldY = vector.Y;
        
        vector.X = vector.X * M11 + vector.Y * M12 + vector.Z * M13;
        vector.Y = oldX * M21 + vector.Y * M22 + vector.Z * M23;
        vector.Z = oldX * M31 + oldY * M32 + vector.Z * M33;
    }

    const std::vector<float> Matrix3f::ToArray() const noexcept
    {
        return {M11, M12, M13, M21, M22, M23, M31, M32, M33};
    }
}

FaceEngine::Vector2f operator *(const FaceEngine::Matrix3f& matrix, const FaceEngine::Vector2f& vector) noexcept
{
    return FaceEngine::Vector2f(vector.X * matrix.M11 + vector.Y * matrix.M12 + matrix.M13, vector.X * matrix.M21 + vector.Y * matrix.M22 + matrix.M23);
}

FaceEngine::Vector3f operator *(const FaceEngine::Matrix3f& matrix, const FaceEngine::Vector3f& vector) noexcept
{
    return FaceEngine::Vector3f(vector.X * matrix.M11 + vector.Y * matrix.M12 + vector.Z * matrix.M13, 
                                vector.X * matrix.M21 + vector.Y * matrix.M22 + vector.Z * matrix.M23,
                                vector.X * matrix.M31 + vector.Y * matrix.M32 + vector.Z * matrix.M33);
}