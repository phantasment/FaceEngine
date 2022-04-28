#include "FaceEngine/Math/Vector3f.h"
#include <cmath>

namespace FaceEngine
{
    const Vector3f Vector3f::Zero = Vector3f(0, 0, 0);
    const Vector3f Vector3f::One = Vector3f(1, 1, 1);
    const Vector3f Vector3f::UnitX = Vector3f(1, 0, 0);
    const Vector3f Vector3f::UnitY = Vector3f(0, 1, 0);
    const Vector3f Vector3f::UnitZ = Vector3f(0, 0, 1);

    Vector3f::Vector3f()
    {
        X = 0;
        Y = 0;
        Z = 0;
    }

    Vector3f::Vector3f(float value)
    {
        X = value;
        Y = value;
        Z = value;
    }

    Vector3f::Vector3f(const Vector2f& vector, float z)
    {
        X = vector.X;
        Y = vector.Y;
        Z = z;
    }

    Vector3f::Vector3f(float x, float y, float z)
    {
        X = x;
        Y = y;
        Z = z;
    }

    float Vector3f::Dot(const Vector3f& vector)
    {
        return (X * vector.X) + (Y * vector.Y) + (Z * vector.Z);
    }

    float Vector3f::GetMagnitude()
    {
        return sqrt((X * X) + (Y * Y) + (Z * Z));
    }

    void Vector3f::Add(const Vector3f& vector)
    {
        X += vector.X;
        Y += vector.Y;
        Z += vector.Z;
    }

    void Vector3f::Subtract(const Vector3f& vector)
    {
        X -= vector.X;
        Y -= vector.Y;
        Z -= vector.Z;
    }

    void Vector3f::Multiply(const float& scalar)
    {
        X *= scalar;
        Y *= scalar;
        Z *= scalar;
    }

    void Vector3f::Divide(const float& scalar)
    {
        X /= scalar;
        Y /= scalar;
        Z /= scalar;
    }

    void Vector3f::operator +=(const Vector3f& vector)
    {
        X += vector.X;
        Y += vector.Y;
        Z += vector.Z;
    }

    void Vector3f::operator -=(const Vector3f& vector)
    {
        X -= vector.X;
        Y -= vector.Y;
        Z -= vector.Z;
    }

    void Vector3f::operator *=(const float& scalar)
    {
        X *= scalar;
        Y *= scalar;
        Z *= scalar;
    }

    void Vector3f::operator /=(const float& scalar)
    {
        X /= scalar;
        Y /= scalar;
        Z /= scalar;
    }

    const std::vector<float> Vector3f::ToArray() const noexcept
    {
        return {X, Y, Z};
    }
}

FaceEngine::Vector3f operator +(const FaceEngine::Vector3f& firstVector, const FaceEngine::Vector3f& secondVector)
{
    return FaceEngine::Vector3f(firstVector.X + secondVector.X, firstVector.Y + secondVector.Y, firstVector.Z + secondVector.Z);
}

FaceEngine::Vector3f operator -(const FaceEngine::Vector3f& firstVector, const FaceEngine::Vector3f& secondVector)
{
    return FaceEngine::Vector3f(firstVector.X - secondVector.X, firstVector.Y - secondVector.Y, firstVector.Z - secondVector.Z);
}

FaceEngine::Vector3f operator *(const FaceEngine::Vector3f& vector, const float& scalar)
{
    return FaceEngine::Vector3f(vector.X * scalar, vector.Y * scalar, vector.Z * scalar);
}

FaceEngine::Vector3f operator /(const FaceEngine::Vector3f& vector, const float& scalar)
{
    return FaceEngine::Vector3f(vector.X / scalar, vector.Y / scalar, vector.Z / scalar);
}

FaceEngine::Vector3f operator ==(const FaceEngine::Vector3f& firstVector, const FaceEngine::Vector3f& secondVector)
{
    return firstVector.X == secondVector.X && firstVector.Y == secondVector.Y && firstVector.Z == secondVector.Z;
}

FaceEngine::Vector3f operator !=(const FaceEngine::Vector3f& firstVector, const FaceEngine::Vector3f& secondVector)
{
    return firstVector.X != secondVector.X || firstVector.Y != secondVector.Y || firstVector.Z != secondVector.Z;
}