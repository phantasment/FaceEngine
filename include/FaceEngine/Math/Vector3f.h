#ifndef FACEENGINE_MATH_VECTOR3F_H_
#define FACEENGINE_MATH_VECTOR3F_H_

#include "FaceEngine/Math/Vector.h"
#include "FaceEngine/Math/Vector2f.h"

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

        Vector3f();
        Vector3f(float value);
        Vector3f(const Vector2f& vector, float z);
        Vector3f(float x, float y, float z);

        float Dot(const Vector3f& vector);
        Vector3f Cross(const Vector3f& vector);
        float GetMagnitude();

        void Add(const Vector3f& vector);
        void Subtract(const Vector3f& vector);
        void Multiply(const float& scalar);
        void Divide(const float& scalar);
        bool Equals(const Vector3f& vector);

        void operator +=(const Vector3f& vector);
        void operator -=(const Vector3f& vector);
        void operator *=(const float& scalar);
        void operator /=(const float& scalar);

        const std::vector<float> ToArray() const noexcept override;
    };

    Vector3f operator +(const Vector3f& firstVector, const Vector3f& secondVector);
    Vector3f operator -(const Vector3f& firstVector, const Vector3f& secondVector);
    Vector3f operator *(const Vector3f& vector, const float& scalar);
    Vector3f operator /(const Vector3f& vector, const float& scalar);
    bool operator ==(const Vector3f& firstVector, const Vector3f& secondVector);
    bool operator !=(const Vector3f& firstVector, const Vector3f& secondVector);
}

#endif