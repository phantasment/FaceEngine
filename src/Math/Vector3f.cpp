#include "FaceEngine/Math/Vector3f.h"
#include "FaceEngine/Math/Matrix4f.h"
#include <cmath>
#include <algorithm>

namespace FaceEngine
{
    const Vector3f Vector3f::Zero = Vector3f(0, 0, 0);
    const Vector3f Vector3f::One = Vector3f(1, 1, 1);
    const Vector3f Vector3f::UnitX = Vector3f(1, 0, 0);
    const Vector3f Vector3f::UnitY = Vector3f(0, 1, 0);
    const Vector3f Vector3f::UnitZ = Vector3f(0, 0, 1);

    Vector3f::Vector3f() noexcept
    {
        X = 0;
        Y = 0;
        Z = 0;
    }

    Vector3f::Vector3f(float value) noexcept
    {
        X = value;
        Y = value;
        Z = value;
    }

    Vector3f::Vector3f(const Vector2f& vector, float z) noexcept
    {
        X = vector.X;
        Y = vector.Y;
        Z = z;
    }

    Vector3f::Vector3f(float x, float y, float z) noexcept
    {
        X = x;
        Y = y;
        Z = z;
    }

    float Vector3f::Dot(const Vector3f& vector) const noexcept
    {
        return (X * vector.X) + (Y * vector.Y) + (Z * vector.Z);
    }

    Vector3f Vector3f::Cross(const Vector3f& vector) const noexcept
    {
        return Vector3f(Y * vector.Z - Z * vector.Y, Z * vector.X - X * vector.Z, X * vector.Y - Y * vector.X);
    }

    float Vector3f::GetMagnitude() const noexcept
    {
        return sqrt((X * X) + (Y * Y) + (Z * Z));
    }

    float Vector3f::Distance(const Vector3f& vector) const noexcept
    {
        return sqrt(((X - vector.X) * (X - vector.X)) + ((Y - vector.Y) * (Y - vector.Y)) + ((Z - vector.Z) * (Z - vector.Z)));
    }

    std::string Vector3f::ToString() const noexcept
    {
        return "Vector3f[X: " + std::to_string(X) + ", Y: " + std::to_string(Y) + ", Z: " + std::to_string(Z) + "]";
    }

    void Vector3f::Add(const Vector3f& vector) noexcept
    {
        X += vector.X;
        Y += vector.Y;
        Z += vector.Z;
    }

    void Vector3f::Subtract(const Vector3f& vector) noexcept
    {
        X -= vector.X;
        Y -= vector.Y;
        Z -= vector.Z;
    }

    void Vector3f::Multiply(const float scalar) noexcept
    {
        X *= scalar;
        Y *= scalar;
        Z *= scalar;
    }

    void Vector3f::Multiply(const Vector3f& vector) noexcept
    {
        X *= vector.X;
        Y *= vector.Y;
        Z *= vector.Z;
    }

    void Vector3f::Divide(const float scalar)
    {
        X /= scalar;
        Y /= scalar;
        Z /= scalar;
    }

    void Vector3f::Transform(const Matrix3f& matrix) noexcept
    {
        float oldX = X;
        float oldY = Y;

        X = X * matrix.M11 + Y * matrix.M12 + Z * matrix.M13;
        Y = oldX * matrix.M21 + Y * matrix.M22 + Z * matrix.M23;
        Z = oldX * matrix.M31 + oldY * matrix.M32 + Z * matrix.M33;
    }

    void Vector3f::Transform(const Matrix4f& matrix) noexcept
    {
        float oldX = X;
        float oldY = Y;

        X = X * matrix.M11 + Y * matrix.M12 + Z * matrix.M13 + matrix.M14;
        Y = oldX * matrix.M21 + Y * matrix.M22 + Z * matrix.M23 + matrix.M24;
        Z = oldX * matrix.M31 + oldY * matrix.M32 + Z * matrix.M33 + matrix.M34;
    }

    bool Vector3f::Equals(const Vector3f& vector) const noexcept
    {
        return X == vector.X && Y == vector.Y && Z == vector.Z;
    }

    void Vector3f::Negate() noexcept
    {
        X = -X;
        Y = -Y;
        Z = -Z;
    }

    void Vector3f::Floor() noexcept
    {
        X = floorf(X);
        Y = floorf(Y);
        Z = floorf(Z);
    }

    void Vector3f::Ceiling() noexcept
    {
        X = ceilf(X);
        Y = ceilf(Y);
        Z = ceilf(Z);
    }

    void Vector3f::Round() noexcept
    {
        X = roundf(X);
        Y = roundf(Y);
        Z = roundf(Z);
    }

    void Vector3f::Clamp(const Vector3f& firstBound, const Vector3f& secondBound) noexcept
    {
        X = std::clamp(X, std::min(firstBound.X, secondBound.X), std::max(firstBound.X, secondBound.X));
        Y = std::clamp(Y, std::min(firstBound.Y, secondBound.Y), std::max(firstBound.Y, secondBound.Y));
        Z = std::clamp(Z, std::min(firstBound.Z, secondBound.Z), std::max(firstBound.Z, secondBound.Z));
    }

    void Vector3f::Normalise() noexcept
    {
        float magnitude = GetMagnitude();

        if (magnitude != 0)
        {
            X /= magnitude;
            Y /= magnitude;
            Z /= magnitude;
        }
    }

    void Vector3f::operator +=(const Vector3f& vector) noexcept
    {
        X += vector.X;
        Y += vector.Y;
        Z += vector.Z;
    }

    void Vector3f::operator -=(const Vector3f& vector) noexcept
    {
        X -= vector.X;
        Y -= vector.Y;
        Z -= vector.Z;
    }

    void Vector3f::operator *=(const float scalar) noexcept
    {
        X *= scalar;
        Y *= scalar;
        Z *= scalar;
    }

    void Vector3f::operator *=(const Vector3f& vector) noexcept
    {
        X *= vector.X;
        Y *= vector.Y;
        Z *= vector.Z;
    }

    void Vector3f::operator *=(const Matrix3f& matrix) noexcept
    {
        Transform(matrix);
    }

    void Vector3f::operator *=(const Matrix4f& matrix) noexcept
    {
        Transform(matrix);
    }

    void Vector3f::operator /=(const float scalar)
    {
        if (scalar == 0)
        {
            throw Exception::FromMessage("Vector3f::operator /=", "Divisor cannot be zero.");
        }

        X /= scalar;
        Y /= scalar;
        Z /= scalar;
    }

    Vector3f Vector3f::operator -() const noexcept
    {
        return Vector3f(-X, -Y, -Z);
    }

    float Vector3f::operator [](int index) const
    {
        if (index == 0)
        {
            return X;
        }
        else if (index == 1)
        {
            return Y;
        }
        else if (index == 2)
        {
            return Z;
        }
        else
        {
            throw Exception::FromMessage("Vector3f::operator []", "Index out of bounds of Vector3f.");
        }
    }

    float& Vector3f::operator [](int index)
    {
        if (index == 0)
        {
            return X;
        }
        else if (index == 1)
        {
            return Y;
        }
        else if (index == 2)
        {
            return Z;
        }
        else
        {
            throw Exception::FromMessage("Vector3f::operator []", "Index out of bounds of Vector3f.");
        }
    }

    Vector3f Vector3f::Max(const Vector3f& firstVector, const Vector3f& secondVector) noexcept
    {
        return Vector3f(std::max(firstVector.X, secondVector.X), std::max(firstVector.Y, secondVector.Y), std::max(firstVector.Z, secondVector.Z));
    }

    Vector3f Vector3f::Min(const Vector3f& firstVector, const Vector3f& secondVector) noexcept
    {
        return Vector3f(std::min(firstVector.X, secondVector.X), std::min(firstVector.Y, secondVector.Y), std::min(firstVector.Z, secondVector.Z));
    }

    Vector3f Vector3f::Lerp(const Vector3f& firstVector, const Vector3f& secondVector, const float t) noexcept
    {
        return Vector3f(firstVector.X + (secondVector.X - firstVector.X) * t, firstVector.Y + (secondVector.Y - firstVector.Y) * t, firstVector.Z + (secondVector.Z - firstVector.Z) * t);
    }

    const std::vector<float> Vector3f::ToArray() const noexcept
    {
        return {X, Y, Z};
    }
}

FaceEngine::Vector3f operator +(const FaceEngine::Vector3f& firstVector, const FaceEngine::Vector3f& secondVector) noexcept
{
    return FaceEngine::Vector3f(firstVector.X + secondVector.X, firstVector.Y + secondVector.Y, firstVector.Z + secondVector.Z);
}

FaceEngine::Vector3f operator -(const FaceEngine::Vector3f& firstVector, const FaceEngine::Vector3f& secondVector) noexcept
{
    return FaceEngine::Vector3f(firstVector.X - secondVector.X, firstVector.Y - secondVector.Y, firstVector.Z - secondVector.Z);
}

FaceEngine::Vector3f operator *(const FaceEngine::Vector3f& vector, const float scalar) noexcept
{
    return FaceEngine::Vector3f(vector.X * scalar, vector.Y * scalar, vector.Z * scalar);
}

FaceEngine::Vector3f operator *(const FaceEngine::Vector3f& firstVector, const FaceEngine::Vector3f& secondVector) noexcept
{
    return FaceEngine::Vector3f(firstVector.X * secondVector.X, firstVector.Y * secondVector.Y, firstVector.Z * secondVector.Z);
}

FaceEngine::Vector3f operator *(const FaceEngine::Vector3f& vector, const FaceEngine::Matrix3f& matrix) noexcept
{
    return FaceEngine::Vector3f(vector.X * matrix.M11 + vector.Y * matrix.M12 + vector.Z * matrix.M13,
                                vector.X * matrix.M21 + vector.Y * matrix.M22 + vector.Z * matrix.M23,
                                vector.X * matrix.M31 + vector.Y * matrix.M32 + vector.Z * matrix.M33);
}

FaceEngine::Vector3f operator *(const FaceEngine::Vector3f& vector, const FaceEngine::Matrix4f& matrix) noexcept
{
    return FaceEngine::Vector3f(vector.X * matrix.M11 + vector.Y * matrix.M12 + vector.Z * matrix.M13 + matrix.M14,
                                vector.X * matrix.M21 + vector.Y * matrix.M22 + vector.Z * matrix.M23 + matrix.M24,
                                vector.X * matrix.M31 + vector.Y * matrix.M32 + vector.Z * matrix.M33 + matrix.M34);
}

FaceEngine::Vector3f operator /(const FaceEngine::Vector3f& vector, const float& scalar)
{
    if (scalar == 0)
    {
        throw FaceEngine::Exception::FromMessage("FaceEngine::Vector3f operator /", "Divisor cannot be zero.");
    }

    return FaceEngine::Vector3f(vector.X / scalar, vector.Y / scalar, vector.Z / scalar);
}

bool operator ==(const FaceEngine::Vector3f& firstVector, const FaceEngine::Vector3f& secondVector) noexcept
{
    return firstVector.X == secondVector.X && firstVector.Y == secondVector.Y && firstVector.Z == secondVector.Z;
}

bool operator !=(const FaceEngine::Vector3f& firstVector, const FaceEngine::Vector3f& secondVector) noexcept
{
    return firstVector.X != secondVector.X || firstVector.Y != secondVector.Y || firstVector.Z != secondVector.Z;
}