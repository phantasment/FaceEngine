#ifndef FACEENGINE_MATH_VECTOR3_H_
#define FACEENGINE_MATH_VECTOR3_H_

#include "FaceEngine/Math/Vector.h"
#include "FaceEngine/Math/Vector2.h"

namespace FaceEngine
{
    template <typename T>
    class Vector3 : FaceEngine::Vector
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

        static const Vector3 Zero;
        static const Vector3 One;
        static const Vector3 UnitX;
        static const Vector3 UnitY;
        static const Vector3 UnitZ;

        Vector3() noexcept
        {
            X = 0;
            Y = 0;
            Z = 0;
        }

        Vector3(T value) noexcept
        {
            X = value;
            Y = value;
            Z = value;
        }

        Vector3(const Vector2<T>& vector, T z) noexcept
        {
            X = vector.X;
            Y = vector.Y;
            Z = z;
        }

        Vector3(T x, T y, T z) noexcept
        {
            X = x;
            Y = y;
            Z = z;
        }

        float Dot(const Vector3& vector) const noexcept
        {
            return (X * vector.X) + (Y * vector.Y) + (Z * vector.Z);
        }

        Vector3<T> Cross(const Vector3& vector) const noexcept
        {
            return Vector3<T>(Y * vector.Z - Z * vector.Y, Z * vector.X - X * vector.Z, X * vector.Y - Y * vector.X);
        }

        float GetMagnitude() const noexcept
        {
            return sqrt((X * X) + (Y * Y) + (Z * Z));
        }

        float Distance(const Vector3& vector) const noexcept
        {
            return sqrt(((X - vector.X) * (X - vector.X)) + ((Y - vector.Y) * (Y - vector.Y)) + ((Z - vector.Z) * (Z - vector.Z)));
        }

        std::string ToString() const noexcept
        {
            return "Vector3[X: " + std::to_string(X) + ", Y: " + std::to_string(Y) + ", Z: " + std::to_string(Z) + "]";
        }

        std::string ToStringWithoutHead() const noexcept
        {
            return "[X: " + std::to_string(X) + ", Y: " + std::to_string(Y) + ", Z: " + std::to_string(Z) + "]";
        }

        void Add(const Vector3& vector) noexcept
        {
            X += vector.X;
            Y += vector.Y;
            Z += vector.Z;
        }

        void Subtract(const Vector3& vector) noexcept
        {
            X -= vector.X;
            Y -= vector.Y;
            Z -= vector.Z;
        }

        void Multiply(const float scalar) noexcept
        {
            X *= scalar;
            Y *= scalar;
            Z *= scalar;
        }

        void Multiply(const Vector3& vector) noexcept
        {
            X *= vector.X;
            Y *= vector.Y;
            Z *= vector.Z;
        }

        void Divide(const float scalar)
        {
            X /= scalar;
            Y /= scalar;
            Z /= scalar;
        }

        bool Equals(const Vector3& vector) const noexcept
        {
            return X == vector.X && Y == vector.Y && Z == vector.Z;
        }

        void Negate() noexcept
        {
            X = -X;
            Y = -Y;
            Z = -Z;
        }

        void Floor() noexcept
        {
            X = floor(X);
            Y = floor(Y);
            Z = floor(Z);
        }

        void Ceiling() noexcept
        {
            X = ceil(X);
            Y = ceil(Y);
            Z = ceil(Z);
        }

        void Round() noexcept
        {
            X = round(X);
            Y = round(Y);
            Z = round(Z);
        }

        void Clamp(const Vector3& firstBound, const Vector3& secondBound) noexcept
        {
            X = std::clamp(X, std::min(firstBound.X, secondBound.X), std::max(firstBound.X, secondBound.X));
            Y = std::clamp(Y, std::min(firstBound.Y, secondBound.Y), std::max(firstBound.Y, secondBound.Y));
            Z = std::clamp(Z, std::min(firstBound.Z, secondBound.Z), std::max(firstBound.Z, secondBound.Z));
        }

        void Normalise() noexcept
        {
            float magnitude = GetMagnitude();

            if (magnitude != 0)
            {
                X /= magnitude;
                Y /= magnitude;
                Z /= magnitude;
            }
        }

        void operator +=(const Vector3& vector) noexcept
        {
            X += vector.X;
            Y += vector.Y;
            Z += vector.Z;
        }
        
        void operator -=(const Vector3& vector) noexcept
        {
            X -= vector.X;
            Y -= vector.Y;
            Z -= vector.Z;
        }

        void operator *=(const T scalar) noexcept
        {
            X *= scalar;
            Y *= scalar;
            Z *= scalar;
        }

        void operator *=(const Vector3& vector) noexcept
        {
            X *= vector.X;
            Y *= vector.Y;
            Z *= vector.Z;
        }

        void operator /=(const T scalar)
        {
            if (scalar == 0)
            {
                throw Exception::FromMessage("Vector3f::operator /=", "Divisor cannot be zero.");
            }

            X /= scalar;
            Y /= scalar;
            Z /= scalar;
        }

        Vector3<T> operator -() const noexcept
        {
            return Vector3<T>(-X, -Y, -Z);
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
            else
            {
                throw Exception::FromMessage("Vector3f::operator []", "Index out of bounds of Vector3f.");
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
            else
            {
                throw Exception::FromMessage("Vector3f::operator []", "Index out of bounds of Vector3f.");
            }
        }

        static Vector3<T> Max(const Vector3& firstVector, const Vector3& secondVector) noexcept
        {
            return Vector3<T>(std::max(firstVector.X, secondVector.X), std::max(firstVector.Y, secondVector.Y), std::max(firstVector.Z, secondVector.Z));
        }

        static Vector3<T> Min(const Vector3& firstVector, const Vector3& secondVector) noexcept
        {
            return Vector3<T>(std::min(firstVector.X, secondVector.X), std::min(firstVector.Y, secondVector.Y), std::min(firstVector.Z, secondVector.Z));
        }

        static Vector3<T> Lerp(const Vector3& firstVector, const Vector3& secondVector, const float t) noexcept
        {
            return Vector3<T>(firstVector.X + (secondVector.X - firstVector.X) * t, firstVector.Y + (secondVector.Y - firstVector.Y) * t, firstVector.Z + (secondVector.Z - firstVector.Z) * t);
        }

        const std::vector<float> ToArray() const noexcept override
        {
            return {X, Y, Z};
        }
    };

    typedef Vector3<float> Vector3f;
}

template <typename T>
const FaceEngine::Vector3<T> FaceEngine::Vector3<T>::Zero(0, 0, 0);

template <typename T>
const FaceEngine::Vector3<T> FaceEngine::Vector3<T>::One(1, 1, 1);

template <typename T>
const FaceEngine::Vector3<T> FaceEngine::Vector3<T>::UnitX(1, 0, 0);

template <typename T>
const FaceEngine::Vector3<T> FaceEngine::Vector3<T>::UnitY(0, 1, 0);

template <typename T>
const FaceEngine::Vector3<T> FaceEngine::Vector3<T>::UnitZ(0, 0, 1);

template <typename T>
FaceEngine::Vector3<T> operator +(const FaceEngine::Vector3<T>& firstVector, const FaceEngine::Vector3<T>& secondVector) noexcept
{
    return FaceEngine::Vector3<T>(firstVector.X + secondVector.X, firstVector.Y + secondVector.Y, firstVector.Z + secondVector.Z);
}

template <typename T>
FaceEngine::Vector3<T> operator -(const FaceEngine::Vector3<T>& firstVector, const FaceEngine::Vector3<T>& secondVector) noexcept
{
    return FaceEngine::Vector3<T>(firstVector.X - secondVector.X, firstVector.Y - secondVector.Y, firstVector.Z - secondVector.Z);
}

template <typename T>
FaceEngine::Vector3<T> operator *(const FaceEngine::Vector3<T>& vector, const float scalar) noexcept
{
    return FaceEngine::Vector3<T>(vector.X * scalar, vector.Y * scalar, vector.Z * scalar);
}

template <typename T>
FaceEngine::Vector3<T> operator *(const FaceEngine::Vector3<T>& firstVector, const FaceEngine::Vector3<T>& secondVector) noexcept
{
    return FaceEngine::Vector3<T>(firstVector.X * secondVector.X, firstVector.Y * secondVector.Y, firstVector.Z * secondVector.Z);
}

template <typename T>
FaceEngine::Vector3<T> operator /(const FaceEngine::Vector3<T>& vector, const float scalar)
{
    if (scalar == 0)
    {
        throw FaceEngine::Exception::FromMessage("FaceEngine::Vector3f operator /", "Divisor cannot be zero.");
    }

    return FaceEngine::Vector3<T>(vector.X / scalar, vector.Y / scalar, vector.Z / scalar);
}

template <typename T>
bool operator ==(const FaceEngine::Vector3<T>& firstVector, const FaceEngine::Vector3<T>& secondVector) noexcept
{
    return firstVector.X == secondVector.X && firstVector.Y == secondVector.Y && firstVector.Z == secondVector.Z;
}

template <typename T>
bool operator !=(const FaceEngine::Vector3<T>& firstVector, const FaceEngine::Vector3<T>& secondVector) noexcept
{
    return firstVector.X != secondVector.X || firstVector.Y != secondVector.Y || firstVector.Z != secondVector.Z;
}

template <typename T>
std::ostream& operator <<(std::ostream& os, const FaceEngine::Vector3<T>& vector)
{
    return os << vector.ToString();
}

#endif