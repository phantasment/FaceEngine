#ifndef FACEENGINE_MATH_MATRIX4F_H_
#define FACEENGINE_MATH_MATRIX4F_H_

#include "FaceEngine/Math/Matrix.h"
#include "FaceEngine/Math/Vector4f.h"
#include "FaceEngine/Math/Vector3f.h"

namespace FaceEngine
{
    class Matrix4f : public Matrix
    {
    public:
        float M11, M12, M13, M14, M21, M22, M23, M24, M31, M32, M33, M34, M41, M42, M43, M44;

        Matrix4f();
        Matrix4f(const Matrix4f& matrix);
        Matrix4f(const float& m11, const float& m12, const float& m13, const float& m14, const float& m21, const float& m22, const float& m23, const float& m24, 
        const float& m31, const float& m32, const float& m33, const float& m34, const float& m41, const float& m42, const float& m43, const float& m44);

        float GetDeterminant() const;
        Matrix4f GetInverse() const;
        Matrix4f GetMinors() const;
        Matrix4f GetCofactors() const;
        Matrix4f GetAdjoint() const;

        void Transpose();
        void Add(const Matrix4f& matrix);
        void Subtract(const Matrix4f& matrix);
        void Multiply(const Matrix4f& matrix);
        void Multiply(const float& scalar);
        void Divide(const float& scalar);

        void Translate(const float& xTranslation, const float& yTranslation, const float& zTranslation);
        void Scale(const float& scale);
        void RotateX(const float& degrees);
        void RotateY(const float& degrees);
        void RotateZ(const float& degrees);

        Vector4f Transform(const Vector4f& vector) const;
        Vector3f TransformHomogeneous(const Vector3f& vector) const;

        static Matrix4f Identity();
        static Matrix4f Zero();
        static Matrix4f CreateTranslation(const float& xTranslation, const float& yTranslation, const float& zTranslation);
        static Matrix4f CreateScale(const float& xScale, const float& yScale, const float& zScale);
        static Matrix4f CreateRotationX(const float& angle);
        static Matrix4f CreateRotationY(const float& angle);
        static Matrix4f CreateRotationZ(const float& angle);
        static Matrix4f CreatePerspective(const float& fieldOfView, const float& aspectRatio, const float& nearPlane, const float& farPlane);
        static Matrix4f CreateOrthographic(const float& width, const float& height, const float& nearPlane, const float& farPlane);

        void operator +=(const Matrix4f& matrix);
        void operator -=(const Matrix4f& matrix);
        void operator *=(const Matrix4f& matrix);
        void operator *=(const float& scalar);
        void operator /=(const float& scalar);

        const std::vector<float> ToArray() const noexcept override;
        std::string ToString() const;
        std::string ToStringInline() const;
    };

    Matrix4f operator +(const Matrix4f& firstMatrix, const Matrix4f& secondMatrix);
    Matrix4f operator -(const Matrix4f& firstMatrix, const Matrix4f& secondMatrix);
    Matrix4f operator *(const Matrix4f& firstMatrix, const Matrix4f& secondMatrix);
    Matrix4f operator *(const Matrix4f& matrix, const float& scalar);
    Vector4f operator *(const Matrix4f& matrix, const Vector4f& vector);
    Vector3f operator *(const Matrix4f& matrix, const Vector3f& vector);
    Matrix4f operator /(const Matrix4f& matrix, const float& scalar);

    std::ostream& operator <<(std::ostream& cout, const Matrix4f& matrix);
}

#endif