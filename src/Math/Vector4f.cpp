#include "FaceEngine/Math/Vector4f.h"

#include <cmath>
#include <algorithm>

namespace FaceEngine
{
    const Vector4f Vector4f::Zero = Vector4f(0, 0, 0, 0);
    const Vector4f Vector4f::One = Vector4f(1, 1, 1, 1);
    const Vector4f Vector4f::UnitX = Vector4f(1, 0, 0, 0);
    const Vector4f Vector4f::UnitY = Vector4f(0, 1, 0, 0);
    const Vector4f Vector4f::UnitZ = Vector4f(0, 0, 1, 0);
    const Vector4f Vector4f::UnitW = Vector4f(0, 0, 0, 1);

    Vector4f::Vector4f() noexcept
    {
        X = 0;
        Y = 0;
        Z = 0;
        W = 0;
    }

    Vector4f::Vector4f(float value) noexcept
    {
        X = value;
        Y = value;
        Z = value;
        W = value;
    }

    Vector4f::Vector4f(const Vector2f& vector, float z, float w) noexcept
    {
        X = vector.X;
        Y = vector.Y;
        Z = z;
        W = w;
    }

    Vector4f::Vector4f(const Vector3f& vector, float w) noexcept
    {
        X = vector.X;
        Y = vector.Y;
        Z = vector.Z;
        W = w;
    }

    Vector4f::Vector4f(float x, float y, float z, float w) noexcept
    {
        X = x;
        Y = y;
        Z = z;
        W = w;
    }

    float Vector4f::Dot(const Vector4f& vector) const noexcept
    {
        return (X * vector.X) + (Y * vector.Y) + (Z * vector.Z) + (W * vector.W);
    }

    float Vector4f::GetMagnitude() const noexcept
    {
        return sqrt((X * X) + (Y * Y) + (Z * Z) + (W * W));
    }

    float Vector4f::Distance(const Vector4f& vector) const noexcept
    {
        return sqrt(((X - vector.X) * (X - vector.X)) + ((Y - vector.Y) * (Y - vector.Y)) + ((Z - vector.Z) * (Z - vector.Z))+ ((W - vector.W) * (W - vector.W)));
    }

    std::string Vector4f::ToString() const noexcept
    {
        return "Vector4f[X: " + std::to_string(X) + ", Y: " + std::to_string(Y) + ", Z: " + std::to_string(Z) + ", W: " + std::to_string(W) + "]";
    }

    void Vector4f::Add(const Vector4f& vector) noexcept
    {
        X += vector.X;
        Y += vector.Y;
        Z += vector.Z;
        W += vector.W;
    }

    void Vector4f::Subtract(const Vector4f& vector) noexcept
    {
        X -= vector.X;
        Y -= vector.Y;
        Z -= vector.Z;
        W -= vector.W;
    }

    void Vector4f::Multiply(const float scalar) noexcept
    {
        X *= scalar;
        Y *= scalar;
        Z *= scalar;
        W *= scalar;
    }

    void Vector4f::Multiply(const Vector4f& vector) noexcept
    {
        X *= vector.X;
        Y *= vector.Y;
        Z *= vector.Z;
        W *= vector.W;
    }

    void Vector4f::Divide(const float scalar)
    {
        if (scalar == 0)
        {
            throw Exception::FromMessage("Vector4f::Divide", "Divisor cannot be zero.");
        }

        X /= scalar;
        Y /= scalar;
        Z /= scalar;
        W /= scalar;
    }

    bool Vector4f::Equals(const Vector4f& vector) const noexcept
    {
        return X == vector.X && Y == vector.Y && Z == vector.Z && W == vector.W;
    }

    void Vector4f::Negate() noexcept
    {
        X = -X;
        Y = -Y;
        Z = -Z;
        W = -W;
    }

    void Vector4f::Floor() noexcept
    {
        X = floorf(X);
        Y = floorf(Y);
        Z = floorf(Z);
        W = floorf(W);
    }

    void Vector4f::Ceiling() noexcept
    {
        X = ceilf(X);
        Y = ceilf(Y);
        Z = ceilf(Z);
        W = ceilf(W);
    }

    void Vector4f::Round() noexcept
    {
        X = roundf(X);
        Y = roundf(Y);
        Z = roundf(Z);
        W = roundf(W);
    }

    void Vector4f::Clamp(const Vector4f& firstBound, const Vector4f& secondBound) noexcept
    {
        X = std::clamp(X, std::min(firstBound.X, secondBound.X), std::max(firstBound.X, secondBound.X));
        Y = std::clamp(Y, std::min(firstBound.Y, secondBound.Y), std::max(firstBound.Y, secondBound.Y));
        Z = std::clamp(Z, std::min(firstBound.Z, secondBound.Z), std::max(firstBound.Z, secondBound.Z));
        W = std::clamp(W, std::min(firstBound.W, secondBound.W), std::max(firstBound.W, secondBound.W));
    }

    void Vector4f::Normalise() noexcept
    {
        float magnitude = GetMagnitude();

        if (magnitude != 0)
        {
            X /= magnitude;
            Y /= magnitude;
            Z /= magnitude;
            W /= magnitude;
        }
    }

    void Vector4f::operator +=(const Vector4f& vector) noexcept
    {
        X += vector.X;
        Y += vector.Y;
        Z += vector.Z;
        W += vector.W;
    }

    void Vector4f::operator -=(const Vector4f& vector) noexcept
    {
        X -= vector.X;
        Y -= vector.Y;
        Z -= vector.Z;
        W -= vector.W;
    }

    void Vector4f::operator *=(const float scalar) noexcept
    {
        X *= scalar;
        Y *= scalar;
        Z *= scalar;
        W *= scalar;
    }

    void Vector4f::operator *=(const Vector4f& vector) noexcept
    {
        X *= vector.X;
        Y *= vector.Y;
        Z *= vector.Z;
        W *= vector.W;
    }

    void Vector4f::operator /=(const float scalar)
    {
        if (scalar == 0)
        {
            throw Exception::FromMessage("Vector4f::operator /=", "Divisor cannot be zero.");
        }

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

FaceEngine::Vector4f operator +(const FaceEngine::Vector4f& firstVector, const FaceEngine::Vector4f& secondVector) noexcept
{
    return FaceEngine::Vector4f(firstVector.X + secondVector.X, firstVector.Y + secondVector.Y, firstVector.Z + secondVector.Z, firstVector.W + secondVector.W);
}

FaceEngine::Vector4f operator -(const FaceEngine::Vector4f& firstVector, const FaceEngine::Vector4f& secondVector) noexcept
{
    return FaceEngine::Vector4f(firstVector.X - secondVector.X, firstVector.Y - secondVector.Y, firstVector.Z - secondVector.Z, firstVector.W - secondVector.W);
}

FaceEngine::Vector4f operator *(const FaceEngine::Vector4f& vector, const float scalar) noexcept
{
    return FaceEngine::Vector4f(vector.X * scalar, vector.Y * scalar, vector.Z * scalar, vector.W * scalar);
}

FaceEngine::Vector4f operator *(const FaceEngine::Vector4f& firstVector, const FaceEngine::Vector4f& secondVector) noexcept
{
    return FaceEngine::Vector4f(firstVector.X * secondVector.X, firstVector.Y * secondVector.Y, firstVector.Z * secondVector.Z, firstVector.W * secondVector.W);
}

FaceEngine::Vector4f operator /(const FaceEngine::Vector4f& vector, const float scalar)
{
    if (scalar == 0)
    {
        throw FaceEngine::Exception::FromMessage("FaceEngine::Vector4f operator /", "Divisor cannot be zero.");
    }

    return FaceEngine::Vector4f(vector.X / scalar, vector.Y / scalar, vector.Z / scalar, vector.W / scalar);
}

bool operator ==(const FaceEngine::Vector4f& firstVector, const FaceEngine::Vector4f& secondVector) noexcept
{
    return firstVector.X == secondVector.X && firstVector.Y == secondVector.Y && firstVector.Z == secondVector.Z && firstVector.W == secondVector.W;
}

bool operator !=(const FaceEngine::Vector4f& firstVector, const FaceEngine::Vector4f& secondVector) noexcept
{
    return firstVector.X != secondVector.X || firstVector.Y != secondVector.Y || firstVector.Z != secondVector.Z || firstVector.W != secondVector.W;
}

std::ostream& operator <<(std::ostream& os, const FaceEngine::Vector4f& vector)
{
    return os << vector.ToString();
}