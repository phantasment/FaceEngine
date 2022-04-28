#include "FaceEngine/Math/Vector2f.h"

#include <cmath>
#include <algorithm>

namespace FaceEngine
{
    const Vector2f Vector2f::Zero = Vector2f(0, 0);
    const Vector2f Vector2f::One = Vector2f(1, 1);
    const Vector2f Vector2f::UnitX = Vector2f(1, 0);
    const Vector2f Vector2f::UnitY = Vector2f(0, 1);

    Vector2f::Vector2f()
    {
        X = 0;
        Y = 0;
    }

    Vector2f::Vector2f(float value)
    {
        X = value;
        Y = value;
    }

    Vector2f::Vector2f(float x, float y)
    {
        X = x;
        Y = y;
    }

    float Vector2f::Dot(const Vector2f& vector) const noexcept
    {
        return (X * vector.X) + (Y * vector.Y);
    }

    float Vector2f::GetMagnitude() const noexcept
    {
        return sqrt((X * X) + (Y * Y));
    }

    float Vector2f::Distance(const Vector2f& vector) const noexcept
    {
        return sqrt(((X - vector.X) * (X - vector.X)) + ((Y - vector.Y) * (Y - vector.Y)));
    }

    std::string Vector2f::ToString() const noexcept
    {
        return "Vector2f[X: " + std::to_string(X) + ", Y: " + std::to_string(Y) + "]";
    }

    void Vector2f::Add(const Vector2f& vector) noexcept
    {
        X += vector.X;
        Y += vector.Y;
    }

    void Vector2f::Subtract(const Vector2f& vector) noexcept
    {
        X -= vector.X;
        Y -= vector.Y;
    }

    void Vector2f::Multiply(const float scalar) noexcept
    {
        X *= scalar;
        Y *= scalar;
    }

    void Vector2f::Multiply(const Vector2f& vector) noexcept
    {
        X *= vector.X;
        Y *= vector.Y;
    }

    void Vector2f::Transform(const Matrix3f& matrix) noexcept
    {
        X *= matrix.M11 * X + matrix.M12 * Y + matrix.M13;
        Y *= matrix.M21 * X + matrix.M22 * Y + matrix.M23;
    }

    void Vector2f::Divide(const float scalar)
    {
        if (scalar == 0)
        {
            throw Exception::FromMessage("Vector2f::Divide", "Divisor cannot be zero.");
        }

        X /= scalar;
        Y /= scalar;
    }

    bool Vector2f::Equals(const Vector2f& vector) const noexcept
    {
        return X == vector.X && Y == vector.Y;
    }

    void Vector2f::Negate() noexcept
    {
        X = -X;
        Y = -Y;
    }

    void Vector2f::Floor() noexcept
    {
        X = floorf(X);
        Y = floorf(Y);
    }

    void Vector2f::Ceiling() noexcept
    {
        X = ceilf(X);
        Y = ceilf(Y);
    }

    void Vector2f::Round() noexcept
    {
        X = roundf(X);
        Y = roundf(Y);
    }

    void Vector2f::Clamp(const Vector2f& firstBound, const Vector2f& secondBound) noexcept
    {
        X = std::clamp(X, std::min(firstBound.X, secondBound.X), std::max(firstBound.X, secondBound.X));
        Y = std::clamp(Y, std::min(firstBound.Y, secondBound.Y), std::max(firstBound.Y, secondBound.Y));
    }

    void Vector2f::Normalise() noexcept
    {
        float magnitude = GetMagnitude();

        if (magnitude != 0)
        {
            X /= magnitude;
            Y /= magnitude;
        }
    }

    void Vector2f::operator +=(const Vector2f& vector) noexcept
    {
        X += vector.X;
        Y += vector.Y;
    }

    void Vector2f::operator -=(const Vector2f& vector) noexcept
    {
        X -= vector.X;
        Y -= vector.Y;
    }

    void Vector2f::operator *=(const float scalar) noexcept
    {
        X *= scalar;
        Y *= scalar;
    }

    void Vector2f::operator *=(const Vector2f& vector) noexcept
    {
        X *= vector.X;
        Y *= vector.Y;
    }

    void Vector2f::operator *=(const Matrix3f& matrix) noexcept
    {
        Transform(matrix);
    }

    void Vector2f::operator /=(const float scalar)
    {
        if (scalar == 0)
        {
            throw std::invalid_argument("Divisor cannot be zero.");
        }

        X /= scalar;
        Y /= scalar;
    }

    Vector2f Vector2f::operator -() const noexcept
    {
        return Vector2f(-X, -Y);
    }

    const std::vector<float> Vector2f::ToArray() const noexcept
    {
        return {X, Y};
    }

    float Vector2f::operator [](int index) const
    {
        if (index == 0)
        {
            return X;
        }
        else if (index == 1)
        {
            return Y;
        }
        else
        {
            throw Exception::FromMessage("Vector2f::operator[]", "Index out of bounds of Vector2f.");
        }
    }

    float& Vector2f::operator [](int index)
    {
        if (index == 0)
        {
            return X;
        }
        else if (index == 1)
        {
            return Y;
        }
        else
        {
            throw std::invalid_argument("Index out of bounds of Vector2f.");
        }
    }

    Vector2f Vector2f::Max(const Vector2f& firstVector, const Vector2f& secondVector) noexcept
    {
        return Vector2f(std::max(firstVector.X, secondVector.X), std::max(firstVector.Y, secondVector.Y));
    }

    Vector2f Vector2f::Min(const Vector2f& firstVector, const Vector2f& secondVector) noexcept
    {
        return Vector2f(std::min(firstVector.X, secondVector.X), std::min(firstVector.Y, secondVector.Y));
    }

    Vector2f Vector2f::Lerp(const Vector2f& firstVector, const Vector2f& secondVector, const float t) noexcept
    {
        return Vector2f(firstVector.X + (secondVector.X - firstVector.X) * t, firstVector.Y + (secondVector.Y - firstVector.Y) * t);
    }
}

FaceEngine::Vector2f operator +(const FaceEngine::Vector2f& firstVector, const FaceEngine::Vector2f& secondVector) noexcept
{
    return FaceEngine::Vector2f(firstVector.X + secondVector.X, firstVector.Y + secondVector.Y);
}

FaceEngine::Vector2f operator -(const FaceEngine::Vector2f& firstVector, const FaceEngine::Vector2f& secondVector) noexcept
{
    return FaceEngine::Vector2f(firstVector.X - secondVector.X, firstVector.Y - secondVector.Y);
}

FaceEngine::Vector2f operator *(const FaceEngine::Vector2f& vector, const float scalar) noexcept
{
    return FaceEngine::Vector2f(vector.X * scalar, vector.Y * scalar);
}

FaceEngine::Vector2f operator *(const FaceEngine::Vector2f& firstVector, const FaceEngine::Vector2f& secondVector) noexcept
{
    return FaceEngine::Vector2f(firstVector.X * secondVector.X, firstVector.Y * secondVector.Y);
}

FaceEngine::Vector2f operator *(const FaceEngine::Vector2f& vector, const FaceEngine::Matrix3f& matrix) noexcept
{
    return FaceEngine::Vector2f(vector.X * matrix.M11 + vector.Y * matrix.M12 + matrix.M13, vector.X * matrix.M21 + vector.Y * matrix.M22 + matrix.M23);
}

FaceEngine::Vector2f operator /(const FaceEngine::Vector2f& vector, const float scalar)
{
    if (scalar == 0)
    {
        throw FaceEngine::Exception::FromMessage("FaceEngine::Vector2f operator /()", "Divisor cannot be zero.");
    }

    return FaceEngine::Vector2f(vector.X / scalar, vector.Y / scalar);
}

FaceEngine::Vector2f operator ==(const FaceEngine::Vector2f& firstVector, const FaceEngine::Vector2f& secondVector) noexcept
{
    return firstVector.X == secondVector.X && firstVector.Y == secondVector.Y;
}

FaceEngine::Vector2f operator !=(const FaceEngine::Vector2f& firstVector, const FaceEngine::Vector2f& secondVector) noexcept
{
    return firstVector.X != secondVector.X || firstVector.Y != secondVector.Y;
}

std::ostream& operator <<(std::ostream& os, const FaceEngine::Vector2f& vec2)
{
    return os << vec2.ToString();
}