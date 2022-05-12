#ifndef FACEENGINE_MATH_VECTOR3F_H_
#define FACEENGINE_MATH_VECTOR3F_H_

#include "FaceEngine/Math/Vector.h"
#include "FaceEngine/Math/Vector2.h"

namespace FaceEngine
{
    class Vector3f : FaceEngine::Vector
    {
    public:
        float X;
        float Y;
        float Z;

        static const Vector3f Zero;
        static const Vector3f One;
        static const Vector3f UnitX;
        static const Vector3f UnitY;
        static const Vector3f UnitZ;

        Vector3f() noexcept;
        Vector3f(float value) noexcept;
        Vector3f(const Vector2f& vector, float z) noexcept;
        Vector3f(float x, float y, float z) noexcept;

        float Dot(const Vector3f& vector) const noexcept;
        Vector3f Cross(const Vector3f& vector) const noexcept;
        float GetMagnitude() const noexcept;
        float Distance(const Vector3f& vector) const noexcept;
        std::string ToString() const noexcept;
        std::string ToStringWithoutHead() const noexcept;

        void Add(const Vector3f& vector) noexcept;
        void Subtract(const Vector3f& vector) noexcept;
        void Multiply(const float scalar) noexcept;
        void Multiply(const Vector3f& vector) noexcept;
        void Divide(const float scalar);
        bool Equals(const Vector3f& vector) const noexcept;

        void Negate() noexcept;
        void Floor() noexcept;
        void Ceiling() noexcept;
        void Round() noexcept;
        void Clamp(const Vector3f& firstBound, const Vector3f& secondBound) noexcept;
        void Normalise() noexcept;

        void operator +=(const Vector3f& vector) noexcept;
        void operator -=(const Vector3f& vector) noexcept;
        void operator *=(const float scalar) noexcept;
        void operator *=(const Vector3f& vector) noexcept;
        void operator /=(const float scalar);
        Vector3f operator -() const noexcept;
        float operator [](int index) const;
        float& operator [](int index);

        static Vector3f Max(const Vector3f& firstVector, const Vector3f& secondVector) noexcept;
        static Vector3f Min(const Vector3f& firstVector, const Vector3f& secondVector) noexcept;
        static Vector3f Lerp(const Vector3f& firstVector, const Vector3f& secondVector, const float t) noexcept;

        const std::vector<float> ToArray() const noexcept override;
    };
}

FaceEngine::Vector3f operator +(const FaceEngine::Vector3f& firstVector, const FaceEngine::Vector3f& secondVector) noexcept;
FaceEngine::Vector3f operator -(const FaceEngine::Vector3f& firstVector, const FaceEngine::Vector3f& secondVector) noexcept;
FaceEngine::Vector3f operator *(const FaceEngine::Vector3f& vector, const float scalar) noexcept;
FaceEngine::Vector3f operator *(const FaceEngine::Vector3f& firstVector, const FaceEngine::Vector3f& secondVector) noexcept;
FaceEngine::Vector3f operator /(const FaceEngine::Vector3f& vector, const float scalar);
bool operator ==(const FaceEngine::Vector3f& firstVector, const FaceEngine::Vector3f& secondVector) noexcept;
bool operator !=(const FaceEngine::Vector3f& firstVector, const FaceEngine::Vector3f& secondVector) noexcept;
std::ostream& operator <<(std::ostream& os, const FaceEngine::Vector3f& vector);

#endif