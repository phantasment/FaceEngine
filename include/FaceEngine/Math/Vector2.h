#ifndef FACEENGINE_MATH_VECTOR2_H_
#define FACEENGINE_MATH_VECTOR2_H_

#include "FaceEngine/Math/Vector.h"
#include <iostream>
#include <cmath>
#include <algorithm>

namespace FaceEngine
{
    template <typename T>
    class Vector2 : public Vector
    {
    static_assert(std::is_same<float, T>() || 
                  std::is_same<double, T>() ||
                  std::is_same<std::int8_t, T>() ||
                  std::is_same<std::uint8_t, T>() || 
                  std::is_same<std::int16_t, T>() ||
                  std::is_same<std::uint16_t, T>() ||
                  std::is_same<std::int32_t, T>() ||
                  std::is_same<std::uint32_t, T>() ||
                  std::is_same<std::int64_t, T>() ||
                  std::is_same<std::uint64_t, T>());
    public:
        T X;
        T Y;

        static const Vector2 Zero;
        static const Vector2 One;
        static const Vector2 UnitX;
        static const Vector2 UnitY;

        Vector2() noexcept
        {
            X = 0;
            Y = 0;
        }

        Vector2(T value) noexcept
        {
            X = value;
            Y = value;
        }

        Vector2(T x, T y) noexcept
        {
            X = x;
            Y = y;
        }

        float Dot(const Vector2<T>& vector) const noexcept
        {
            return (X * vector.X) + (Y * vector.Y);
        }

        float GetMagnitude() const noexcept
        {
            return sqrt((X * X) + (Y * Y));
        }

        float Distance(const Vector2<T>& vector) const noexcept
        {
            return sqrt(((X - vector.X) * (X - vector.X)) + ((Y - vector.Y) * (Y - vector.Y)));
        }

        float DistanceSquared(const Vector2<T>& vector) const noexcept
        {
            return ((X - vector.X) * (X - vector.X)) + ((Y - vector.Y) * (Y - vector.Y));
        }

        std::string ToString() const noexcept
        {
            return "Vector2[X: " + std::to_string(X) + ", Y: " + std::to_string(Y) + "]";
        }

        void Add(const Vector2<T>& vector) noexcept
        {
            X += vector.X;
            Y += vector.Y;
        }

        void Subtract(const Vector2<T>& vector) noexcept
        {
            X -= vector.X;
            Y -= vector.Y;
        }

        void Multiply(const float scalar) noexcept
        {
            X *= scalar;
            Y *= scalar;
        }

        void Multiply(const Vector2<T>& vector) noexcept
        {
            X *= vector.X;
            Y *= vector.Y;
        }

        void Divide(const float scalar)
        {
            if (scalar == 0)
            {
                throw Exception::FromMessage("Vector2::Divide", "Divisor cannot be zero.");
            }

            X /= scalar;
            Y /= scalar;
        }

        bool Equals(const Vector2<T>& vector) const noexcept
        {
            return X == vector.X && Y == vector.Y;
        }

        void Negate() noexcept
        {
            X = -X;
            Y = -Y;
        }

        void Floor() noexcept
        {
            X = floorf(X);
            Y = floorf(Y);
        }

        void Ceiling() noexcept
        {
            X = ceilf(X);
            Y = ceilf(Y);
        }

        void Round() noexcept
        {
            X = roundf(X);
            Y = roundf(Y);
        }

        void Clamp(const Vector2<T>& firstBound, const Vector2<T>& secondBound) noexcept
        {
            X = std::clamp(X, std::min(firstBound.X, secondBound.X), std::max(firstBound.X, secondBound.X));
            Y = std::clamp(Y, std::min(firstBound.Y, secondBound.Y), std::max(firstBound.Y, secondBound.Y));
        }

        void Normalise() noexcept
        {
            float magnitude = GetMagnitude();

            if (magnitude != 0)
            {
                X /= magnitude;
                Y /= magnitude;
            }
        }

        void operator +=(const Vector2<T>& vector) noexcept
        {
            X += vector.X;
            Y += vector.Y;
        }

        void operator -=(const Vector2<T>& vector) noexcept
        {
            X -= vector.X;
            Y -= vector.Y;
        }

        void operator *=(const float scalar) noexcept
        {
            X *= scalar;
            Y *= scalar;
        }

        void operator *=(const Vector2<T>& vector) noexcept
        {
            X *= vector.X;
            Y *= vector.Y;
        }

        void operator /=(const float scalar)
        {
            if (scalar == 0)
            {
                throw Exception::FromMessage("Vector2::operator /=", "Divisor cannot be zero.");
            }

            X /= scalar;
            Y /= scalar;
        }

        Vector2<T> operator -() const noexcept
        {
            return Vector2f(-X, -Y);
        }

        float operator [](int index) const
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
                throw Exception::FromMessage("Vector2::operator []", "Index out of bounds of Vector2f.");
            }
        }

        float& operator [](int index)
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
                throw Exception::FromMessage("Vector2::operator []", "Index out of bounds of Vector2f.");
            }
        }

        static Vector2<T> Max(const Vector2<T>& firstVector, const Vector2<T>& secondVector) noexcept
        {
            return Vector2f(std::max(firstVector.X, secondVector.X), std::max(firstVector.Y, secondVector.Y));
        }

        static Vector2<T> Min(const Vector2<T>& firstVector, const Vector2<T>& secondVector) noexcept
        {
            return Vector2f(std::min(firstVector.X, secondVector.X), std::min(firstVector.Y, secondVector.Y));
        }

        static Vector2<T> Lerp(const Vector2<T>& firstVector, const Vector2<T>& secondVector, const float t) noexcept
        {
            return Vector2f(firstVector.X + (secondVector.X - firstVector.X) * t, firstVector.Y + (secondVector.Y - firstVector.Y) * t);
        }

        const std::vector<float> ToArray() const noexcept override
        {
            return {(float)X, (float)Y};
        }
    };

    typedef Vector2<float> Vector2f;
}

template <typename T>
const FaceEngine::Vector2<T> FaceEngine::Vector2<T>::Zero(0, 0);

template <typename T>
const FaceEngine::Vector2<T> FaceEngine::Vector2<T>::One(1, 1);

template <typename T>
const FaceEngine::Vector2<T> FaceEngine::Vector2<T>::UnitX(1, 0);

template <typename T>
const FaceEngine::Vector2<T> FaceEngine::Vector2<T>::UnitY(0, 1);

template <typename T>
FaceEngine::Vector2<T> operator +(const FaceEngine::Vector2<T>& firstVector, const FaceEngine::Vector2<T>& secondVector) noexcept
{
    return FaceEngine::Vector2<T>(firstVector.X + secondVector.X, firstVector.Y + secondVector.Y);
}

template <typename T>
FaceEngine::Vector2<T> operator -(const FaceEngine::Vector2<T>& firstVector, const FaceEngine::Vector2<T>& secondVector) noexcept
{
    return FaceEngine::Vector2<T>(firstVector.X - secondVector.X, firstVector.Y - secondVector.Y);
}

template <typename T>
FaceEngine::Vector2<T> operator *(const FaceEngine::Vector2<T>& vector, const float scalar) noexcept
{
    return FaceEngine::Vector2<T>(vector.X * scalar, vector.Y * scalar);
}

template <typename T>
FaceEngine::Vector2<T> operator *(const FaceEngine::Vector2<T>& firstVector, const FaceEngine::Vector2<T>& secondVector) noexcept
{
    return FaceEngine::Vector2<T>(firstVector.X * secondVector.X, firstVector.Y * secondVector.Y);
}

template <typename T>
FaceEngine::Vector2<T> operator /(const FaceEngine::Vector2<T>& vector, const float scalar)
{
    if (scalar == 0)
    {
        throw FaceEngine::Exception::FromMessage("FaceEngine::Vector2 operator /()", "Divisor cannot be zero.");
    }

    return FaceEngine::Vector2<T>(vector.X / scalar, vector.Y / scalar);
}

template <typename T>
bool operator ==(const FaceEngine::Vector2<T>& firstVector, const FaceEngine::Vector2<T>& secondVector) noexcept
{
    return firstVector.X == secondVector.X && firstVector.Y == secondVector.Y;
}

template <typename T>
bool operator !=(const FaceEngine::Vector2<T>& firstVector, const FaceEngine::Vector2<T>& secondVector) noexcept
{
    return firstVector.X != secondVector.X || firstVector.Y != secondVector.Y;
}

template <typename T>
std::ostream& operator <<(std::ostream& os, const FaceEngine::Vector2<T>& vector)
{
    return os << vector.ToString();
}

#endif