#ifndef FACEENGINE_MATH_VECTOR4_H_
#define FACEENGINE_MATH_VECTOR4_H_

#include "FaceEngine/Math/Vector.h"
#include "FaceEngine/Math/Vector3.h"
#include <iostream>

namespace FaceEngine
{
    template <typename T>
    class Vector4 : Vector
    {
    static_assert(std::is_same<float, T>() || 
            std::is_same<int, T>() || 
            std::is_same<double, T>() || 
            std::is_same<short, T>() ||
            std::is_same<long, T>());
    public:
        T X;
        T Y;
        T Z;
        T W;

        static const Vector4 Zero;
        static const Vector4 One;
        static const Vector4 UnitX;
        static const Vector4 UnitY;
        static const Vector4 UnitZ;
        static const Vector4 UnitW;

        Vector4() noexcept
        {
            X = 0;
            Y = 0;
            Z = 0;
            W = 0;
        }

        Vector4(float value) noexcept
        {
            X = value;
            Y = value;
            Z = value;
            W = value;
        }

        Vector4(const Vector2f& vector, float z, float w) noexcept
        {
            X = vector.X;
            Y = vector.Y;
            Z = z;
            W = w;
        }

        Vector4(const Vector3f& vector, float w) noexcept
        {
            X = vector.X;
            Y = vector.Y;
            Z = vector.Z;
            W = w;
        }

        Vector4(float x, float y, float z, float w) noexcept
        {
            X = x;
            Y = y;
            Z = z;
            W = w;
        }

        float Dot(const Vector4& vector) const noexcept
        {
            return (X * vector.X) + (Y * vector.Y) + (Z * vector.Z) + (W * vector.W);
        }

        float GetMagnitude() const noexcept
        {
            return sqrt((X * X) + (Y * Y) + (Z * Z) + (W * W));
        }

        float Distance(const Vector4& vector) const noexcept
        {
            return sqrt(((X - vector.X) * (X - vector.X)) + ((Y - vector.Y) * (Y - vector.Y)) + ((Z - vector.Z) * (Z - vector.Z))+ ((W - vector.W) * (W - vector.W)));
        }

        std::string ToString() const noexcept
        {
            return "Vector4f[X: " + std::to_string(X) + ", Y: " + std::to_string(Y) + ", Z: " + std::to_string(Z) + ", W: " + std::to_string(W) + "]";
        }

        void Add(const Vector4& vector) noexcept
        {
            X += vector.X;
            Y += vector.Y;
            Z += vector.Z;
            W += vector.W;
        }

        void Subtract(const Vector4& vector) noexcept
        {
            X -= vector.X;
            Y -= vector.Y;
            Z -= vector.Z;
            W -= vector.W;
        }

        void Multiply(const float scalar) noexcept
        {
            X *= scalar;
            Y *= scalar;
            Z *= scalar;
            W *= scalar;
        }

        void Multiply(const Vector4& vector) noexcept
        {
            X *= vector.X;
            Y *= vector.Y;
            Z *= vector.Z;
            W *= vector.W;
        }

        void Divide(const float scalar)
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

        bool Equals(const Vector4& vector) const noexcept
        {
            return X == vector.X && Y == vector.Y && Z == vector.Z && W == vector.W;
        }

        void Negate() noexcept
        {
            X = -X;
            Y = -Y;
            Z = -Z;
            W = -W;
        }

        void Floor() noexcept
        {
            X = floorf(X);
            Y = floorf(Y);
            Z = floorf(Z);
            W = floorf(W);
        }

        void Ceiling() noexcept
        {
            X = ceilf(X);
            Y = ceilf(Y);
            Z = ceilf(Z);
            W = ceilf(W);
        }

        void Round() noexcept
        {
            X = roundf(X);
            Y = roundf(Y);
            Z = roundf(Z);
            W = roundf(W);
        }

        void Abs() noexcept
        {
            X = abs(X);
            Y = abs(Y);
            Z = abs(Z);
            W = abs(W);
        }

        void Clamp(const Vector4& firstBound, const Vector4& secondBound) noexcept
        {
            X = std::clamp(X, std::min(firstBound.X, secondBound.X), std::max(firstBound.X, secondBound.X));
            Y = std::clamp(Y, std::min(firstBound.Y, secondBound.Y), std::max(firstBound.Y, secondBound.Y));
            Z = std::clamp(Z, std::min(firstBound.Z, secondBound.Z), std::max(firstBound.Z, secondBound.Z));
            W = std::clamp(W, std::min(firstBound.W, secondBound.W), std::max(firstBound.W, secondBound.W));
        }

        void Normalise() noexcept
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

        void operator +=(const Vector4& vector) noexcept
        {
            X += vector.X;
            Y += vector.Y;
            Z += vector.Z;
            W += vector.W;
        }

        void operator -=(const Vector4& vector) noexcept
        {
            X -= vector.X;
            Y -= vector.Y;
            Z -= vector.Z;
            W -= vector.W;
        }

        void operator *=(const float scalar) noexcept
        {
            X *= scalar;
            Y *= scalar;
            Z *= scalar;
            W *= scalar;
        }

        void operator *=(const Vector4& vector) noexcept
        {
            X *= vector.X;
            Y *= vector.Y;
            Z *= vector.Z;
            W *= vector.W;
        }

        void operator /=(const float scalar)
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

        Vector4<T> operator -() const noexcept
        {
            return Vector4<T>(-X, -Y, -Z, -W);
        }

        T operator [](int index) const
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
            else if (index == 3)
            {
                return W;
            }
            else
            {
                throw Exception::FromMessage("Vector3::operator []", "Index out of bounds of Vector3.");
            }
        }

        T& operator [](int index)
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
            else if (index == 3)
            {
                return W;
            }
            else
            {
                throw Exception::FromMessage("Vector3::operator []", "Index out of bounds of Vector3.");
            }
        }

        static Vector4<T> Max(const Vector4& firstVector, const Vector4& secondVector) noexcept
        {
            return Vector4<T>(std::max(firstVector.X, secondVector.X), std::max(firstVector.Y, secondVector.Y), std::max(firstVector.Z, secondVector.Z), std::max(firstVector.W, secondVector.W));
        }

        static Vector4<T> Min(const Vector4& firstVector, const Vector4& secondVector) noexcept
        {
            return Vector4<T>(std::min(firstVector.X, secondVector.X), std::min(firstVector.Y, secondVector.Y), std::min(firstVector.Z, secondVector.Z), std::min(firstVector.W, secondVector.W));
        }

        static Vector4<T> Lerp(const Vector4& firstVector, const Vector4& secondVector, const float t) noexcept
        {
            return Vector4<T>(firstVector.X + (secondVector.X - firstVector.X) * t, firstVector.Y + (secondVector.Y - firstVector.Y) * t, firstVector.Z + (secondVector.Z - firstVector.Z) * t, firstVector.W + (secondVector.W - firstVector.W) * t);
        }

        const std::vector<float> ToArray() const noexcept override
        {
            return { X, Y, Z, W };
        }
    };

    typedef Vector4<float> Vector4f;
}

template <typename T>
const FaceEngine::Vector4<T> FaceEngine::Vector4<T>::Zero(0, 0, 0, 0);

template <typename T>
const FaceEngine::Vector4<T> FaceEngine::Vector4<T>::One(1, 1, 1, 1);

template <typename T>
const FaceEngine::Vector4<T> FaceEngine::Vector4<T>::UnitX(1, 0, 0, 0);

template <typename T>
const FaceEngine::Vector4<T> FaceEngine::Vector4<T>::UnitY(0, 1, 0, 0);

template <typename T>
const FaceEngine::Vector4<T> FaceEngine::Vector4<T>::UnitZ(0, 0, 1, 0);

template <typename T>
const FaceEngine::Vector4<T> FaceEngine::Vector4<T>::UnitW(0, 0, 0, 1);

template <typename T>
FaceEngine::Vector4<T> operator +(const FaceEngine::Vector4<T>& firstVector, const FaceEngine::Vector4<T>& secondVector) noexcept
{
    return FaceEngine::Vector4<T>(firstVector.X + secondVector.X, firstVector.Y + secondVector.Y, firstVector.Z + secondVector.Z, firstVector.W + secondVector.W);
}

template <typename T>
FaceEngine::Vector4<T> operator -(const FaceEngine::Vector4<T>& firstVector, const FaceEngine::Vector4<T>& secondVector) noexcept
{
    return FaceEngine::Vector4<T>(firstVector.X - secondVector.X, firstVector.Y - secondVector.Y, firstVector.Z - secondVector.Z, firstVector.W - secondVector.W);
}

template <typename T>
FaceEngine::Vector4<T> operator *(const FaceEngine::Vector4<T>& vector, const float scalar) noexcept
{
    return FaceEngine::Vector4<T>(vector.X * scalar, vector.Y * scalar, vector.Z * scalar, vector.W * scalar);
}

template <typename T>
FaceEngine::Vector4<T> operator *(const FaceEngine::Vector4<T>& firstVector, const FaceEngine::Vector4<T>& secondVector) noexcept
{
    return FaceEngine::Vector4<T>(firstVector.X * secondVector.X, firstVector.Y * secondVector.Y, firstVector.Z * secondVector.Z, firstVector.W * secondVector.W);
}

template <typename T>
FaceEngine::Vector4<T> operator /(const FaceEngine::Vector4<T>& vector, const float& scalar)
{
    if (scalar == 0)
    {
        throw FaceEngine::Exception::FromMessage("FaceEngine::Vector4f operator /", "Divisor cannot be zero.");
    }

    return FaceEngine::Vector4<T>(vector.X / scalar, vector.Y / scalar, vector.Z / scalar, vector.W / scalar);
}

template <typename T>
bool operator ==(const FaceEngine::Vector4<T>& firstVector, const FaceEngine::Vector4<T>& secondVector) noexcept
{
    return firstVector.X == secondVector.X && firstVector.Y == secondVector.Y && firstVector.Z == secondVector.Z && firstVector.W == secondVector.W;
}

template <typename T>
bool operator !=(const FaceEngine::Vector4<T>& firstVector, const FaceEngine::Vector4<T>& secondVector) noexcept
{
    return firstVector.X != secondVector.X || firstVector.Y != secondVector.Y || firstVector.Z != secondVector.Z || firstVector.W != secondVector.W;
}

template <typename T>
std::ostream& operator <<(std::ostream& os, const FaceEngine::Vector4<T>& vector)
{
    return os << vector.ToString();
}

#endif