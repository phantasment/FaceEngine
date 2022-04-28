#include "FaceEngine/Math/Vector4f.h"

#include <cmath>

namespace FaceEngine
{
    const Vector4f Vector4f::Zero = Vector4f(0, 0, 0, 0);
    const Vector4f Vector4f::One = Vector4f(1, 1, 1, 1);
    const Vector4f Vector4f::UnitX = Vector4f(1, 0, 0, 0);
    const Vector4f Vector4f::UnitY = Vector4f(0, 1, 0, 0);
    const Vector4f Vector4f::UnitZ = Vector4f(0, 0, 1, 0);
    const Vector4f Vector4f::UnitW = Vector4f(0, 0, 0, 1);

    Vector4f::Vector4f()
    {
        X = 0;
        Y = 0;
        Z = 0;
        W = 0;
    }

    Vector4f::Vector4f(float value)
    {
        X = value;
        Y = value;
        Z = value;
        W = value;
    }

    Vector4f::Vector4f(const Vector3f& vector, float w)
    {
        X = vector.X;
        Y = vector.Y;
        Z = vector.Z;
        W = w;
    }

    Vector4f::Vector4f(float x, float y, float z, float w)
    {
        X = x;
        Y = y;
        Z = z;
        W = w;
    }

    float Vector4f::Dot(const Vector4f& vector)
    {
        return (X * vector.X) + (Y * vector.Y) + (Z * vector.Z) + (W * vector.W);
    }

    float Vector4f::GetMagnitude()
    {
        return sqrt((X * X) + (Y * Y) + (Z * Z) + (W * W));
    }

    void Vector4f::Add(const Vector4f& vector)
    {
        X += vector.X;
        Y += vector.Y;
        Z += vector.Z;
        W += vector.W;
    }

    void Vector4f::Subtract(const Vector4f& vector)
    {
        X -= vector.X;
        Y -= vector.Y;
        Z -= vector.Z;
        W -= vector.W;
    }

    void Vector4f::Multiply(const float& scalar)
    {
        X *= scalar;
        Y *= scalar;
        Z *= scalar;
        W *= scalar;
    }

    void Vector4f::Divide(const float& scalar)
    {
        X /= scalar;
        Y /= scalar;
        Z /= scalar;
        W /= scalar;
    }

    void Vector4f::operator +=(const Vector4f& vector)
    {
        X += vector.X;
        Y += vector.Y;
        Z += vector.Z;
        W += vector.W;
    }

    void Vector4f::operator -=(const Vector4f& vector)
    {
        X -= vector.X;
        Y -= vector.Y;
        Z -= vector.Z;
        W -= vector.W;
    }

    void Vector4f::operator *=(const float& scalar)
    {
        X *= scalar;
        Y *= scalar;
        Z *= scalar;
        W *= scalar;
    }

    void Vector4f::operator /=(const float& scalar)
    {
        X /= scalar;
        Y /= scalar;
        Z /= scalar;
        W /= scalar;
    }

    const std::vector<float> Vector4f::ToArray() const noexcept
    {
        return {X, Y, Z, W};
    }
}

FaceEngine::Vector4f operator +(const FaceEngine::Vector4f& firstVector, const FaceEngine::Vector4f& secondVector)
{
    return FaceEngine::Vector4f(firstVector.X + secondVector.X, firstVector.Y + secondVector.Y, firstVector.Z + secondVector.Z, firstVector.W + secondVector.W);
}

FaceEngine::Vector4f operator -(const FaceEngine::Vector4f& firstVector, const FaceEngine::Vector4f& secondVector)
{
    return FaceEngine::Vector4f(firstVector.X - secondVector.X, firstVector.Y - secondVector.Y, firstVector.Z - secondVector.Z, firstVector.W - secondVector.W);
}

FaceEngine::Vector4f operator *(const FaceEngine::Vector4f& vector, const float& scalar)
{
    return FaceEngine::Vector4f(vector.X * scalar, vector.Y * scalar, vector.Z * scalar, vector.W * scalar);
}

FaceEngine::Vector4f operator /(const FaceEngine::Vector4f& vector, const float& scalar)
{
    return FaceEngine::Vector4f(vector.X / scalar, vector.Y / scalar, vector.Z / scalar, vector.W * scalar);
}

FaceEngine::Vector4f operator ==(const FaceEngine::Vector4f& firstVector, const FaceEngine::Vector4f& secondVector)
{
    return firstVector.X == secondVector.X && firstVector.Y == secondVector.Y && firstVector.Z == secondVector.Z && firstVector.W == secondVector.W;
}

FaceEngine::Vector4f operator !=(const FaceEngine::Vector4f& firstVector, const FaceEngine::Vector4f& secondVector)
{
    return firstVector.X != secondVector.X || firstVector.Y != secondVector.Y || firstVector.Z != secondVector.Z || firstVector.W != secondVector.W;
}