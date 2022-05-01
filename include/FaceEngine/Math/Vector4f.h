#ifndef FACEENGINE_MATH_VECTOR4F_H_
#define FACEENGINE_MATH_VECTOR4F_H_

#include "FaceEngine/Math/Vector.h"
#include "FaceEngine/Math/Vector3f.h"
#include <iostream>

namespace FaceEngine
{
    class Vector4f : FaceEngine::Vector
    {
    public:
        float X;
        float Y;
        float Z;
        float W;

        static const Vector4f Zero;
        static const Vector4f One;
        static const Vector4f UnitX;
        static const Vector4f UnitY;
        static const Vector4f UnitZ;
        static const Vector4f UnitW;

        Vector4f() noexcept;
        Vector4f(float value) noexcept;
        Vector4f(const Vector2f& vector, float z, float w) noexcept;
        Vector4f(const Vector3f& vector, float w) noexcept;
        Vector4f(float x, float y, float z, float w) noexcept;

        float Dot(const Vector4f& vector) const noexcept;
        float GetMagnitude() const noexcept;
        float Distance(const Vector4f& vector) const noexcept;
        std::string ToString() const noexcept;

        void Add(const Vector4f& vector) noexcept;
        void Subtract(const Vector4f& vector) noexcept;
        void Multiply(const float scalar) noexcept;
        void Multiply(const Vector4f& scalar) noexcept;
        void Divide(const float scalar);
        void Transform(const Matrix4f& matrix) noexcept;
        bool Equals(const Vector4f& vector) const noexcept;

        void Negate() noexcept;
        void Floor() noexcept;
        void Ceiling() noexcept;
        void Round() noexcept;
        void Abs() noexcept;
        void Clamp(const Vector4f& firstBound, const Vector4f& secondBound) noexcept;
        void Normalise() noexcept;

        void operator +=(const Vector4f& vector) noexcept;
        void operator -=(const Vector4f& vector) noexcept;
        void operator *=(const float scalar) noexcept;
        void operator *=(const Vector4f& scalar) noexcept;
        void operator *=(const Matrix4f& scalar) noexcept;
        void operator /=(const float scalar);
        Vector4f operator -() const noexcept;
        float operator [](int index) const;
        float& operator [](int index);

        static Vector4f Max(const Vector4f& firstVector, const Vector4f& secondVector) noexcept;
        static Vector4f Min(const Vector4f& firstVector, const Vector4f& secondVector) noexcept;
        static Vector4f Lerp(const Vector4f& firstVector, const Vector4f& secondVector, const float t) noexcept;

        const std::vector<float> ToArray() const noexcept override;
    };
}

FaceEngine::Vector4f operator +(const FaceEngine::Vector4f& firstVector, const FaceEngine::Vector4f& secondVector) noexcept; 
FaceEngine::Vector4f operator -(const FaceEngine::Vector4f& firstVector, const FaceEngine::Vector4f& secondVector) noexcept;
FaceEngine::Vector4f operator *(const FaceEngine::Vector4f& vector, const float scalar) noexcept;
FaceEngine::Vector4f operator *(const FaceEngine::Vector4f& firstVector, const FaceEngine::Vector4f& secondVector) noexcept;
FaceEngine::Vector4f operator *(const FaceEngine::Vector4f& vector, const FaceEngine::Matrix4f& scalar) noexcept;
FaceEngine::Vector4f operator /(const FaceEngine::Vector4f& vector, const float& scalar);
bool operator ==(const FaceEngine::Vector4f& firstVector, const FaceEngine::Vector4f& secondVector) noexcept;
bool operator !=(const FaceEngine::Vector4f& firstVector, const FaceEngine::Vector4f& secondVector) noexcept;

#endif