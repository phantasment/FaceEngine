#ifndef FACEENGINE_MATH_VECTOR4F_H_
#define FACEENGINE_MATH_VECTOR4F_H_

#include "FaceEngine/Math/Vector.h"
#include "FaceEngine/Math/Vector3f.h"

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

        Vector4f();
        Vector4f(float value);
        Vector4f(const Vector3f& vector, float w);
        Vector4f(float x, float y, float z, float w);

        float Dot(const Vector4f& vector);
        float GetMagnitude();

        void Add(const Vector4f& vector);
        void Subtract(const Vector4f& vector);
        void Multiply(const float& scalar);
        void Divide(const float& scalar);
        bool Equals(const Vector4f& vector);

        void operator +=(const Vector4f& vector);
        void operator -=(const Vector4f& vector);
        void operator *=(const float& scalar);
        void operator /=(const float& scalar);

        const std::vector<float> ToArray() const noexcept override;
    };

    Vector4f operator +(const Vector4f& firstVector, const Vector4f& secondVector);
    Vector4f operator -(const Vector4f& firstVector, const Vector4f& secondVector);
    Vector4f operator *(const Vector4f& vector, const float& scalar);
    Vector4f operator /(const Vector4f& vector, const float& scalar);
    bool operator ==(const Vector4f& firstVector, const Vector4f& secondVector);
    bool operator !=(const Vector4f& firstVector, const Vector4f& secondVector);
}

#endif