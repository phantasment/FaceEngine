#ifndef FACEENGINE_MATH_MATRIX4F_H_
#define FACEENGINE_MATH_MATRIX4F_H_

#include "FaceEngine/Math/Matrix.h"
#include "FaceEngine/Math/Vector3f.h"

namespace FaceEngine
{
    class Matrix4f : public Matrix
    {
    public:
        float M11, M12, M13, M14, M21, M22, M23, M24, M31, M32, M33, M34, M41, M42, M43, M44;

        static const Matrix4f Zero;
        static const Matrix4f Identity;

        Matrix4f() noexcept;
        Matrix4f(const Matrix4f& matrix) noexcept;
        Matrix4f(const float m11, const float m12, const float m13, const float m14, 
                 const float m21, const float m22, const float m23, const float m24, 
                 const float m31, const float m32, const float m33, const float m34, 
                 const float m41, const float m42, const float m43, const float m44) noexcept;
        Matrix4f(const Vector3f& rightVector, const Vector3f& upVector, const Vector3f& forwardVector, const Vector3f& translation) noexcept;

        float GetDeterminant() const noexcept;
        Matrix4f GetInverse() const;
        Matrix4f GetMinors() const noexcept;
        Matrix4f GetCofactors() const noexcept;
        Matrix4f GetAdjoint() const noexcept;
        bool Equals(Matrix4f& matrix) const noexcept;

        void Transpose() noexcept;
        void Add(const Matrix4f& matrix) noexcept;
        void Subtract(const Matrix4f& matrix) noexcept;
        void Multiply(const Matrix4f& matrix) noexcept;
        void Multiply(const float scalar) noexcept;
        void Divide(const float scalar);

        void SetRight(const Vector3f& rightVector) noexcept;
        void SetUp(const Vector3f& upVector) noexcept;
        void SetForward(const Vector3f& forwardVector) noexcept;
        void SetTranslation(const float translationX, const float translationY, const float translationZ) noexcept;
        void SetTranslation(const Vector3f& translation) noexcept;
        void SetScale(const float scale) noexcept;
        void SetScale(const float scaleX, const float scaleY, const float scaleZ) noexcept;
        Vector3f GetRight() const noexcept;
        Vector3f GetUp() const noexcept;
        Vector3f GetForward() const noexcept;
        Vector3f GetTranslation() const noexcept;
        Vector3f GetScale() const noexcept;

        static Matrix4f CreateBillboard(Vector3f& objectPos, Vector3f& cameraPos, Vector3f& upVector, Vector3f& forwardVector) noexcept;
        static Matrix4f CreateConstrainedBillboard(Vector3f& objectPos, Vector3f& cameraPos, Vector3f& upVector, Vector3f& forwardVector, Vector3f& rotationAxis) noexcept;
        static Matrix4f CreateLookAt(Vector3f& cameraPos, Vector3f& targetPos, Vector3f& upVector) noexcept;
        static Matrix4f CreateOrthographic(const float width, const float height, const float zNearPlane, const float zFarPlane) noexcept;
        static Matrix4f CreateOrthographicOffCentre(const float left, const float right, const float bottom, const float top, const float zNearPlane, const float zFarPlane) noexcept;
        static Matrix4f CreatePerspective(const float width, const float height, const float nearPlaneDistance, const float farPlaneDistance) noexcept;
        static Matrix4f CreatePerspectiveFOV(const float fieldOfView, const float aspectRatio, const float nearPlane, const float farPlane) noexcept;
        static Matrix4f CreatePerspectiveOffCentre(const float left, const float right, const float bottom, const float top, const float nearPlaneDistance, const float farPlaneDistance) noexcept;
        static Matrix4f CreateWorld(const Vector3f& objectPos, const Vector3f& upVector, const Vector3f& forwardVector) noexcept;
        //static Matrix4f CreateReflection(Plane) noexcept;
        //static Matrix4f CreateShadow(Plane, Vector3 lightSource) noexcept
        static Matrix4f CreateRotationX(const float angle) noexcept;
        static Matrix4f CreateRotationX(const float angle, const Vector3f& position) noexcept;
        static Matrix4f CreateRotationY(const float angle) noexcept;
        static Matrix4f CreateRotationY(const float angle, const Vector3f& position) noexcept;
        static Matrix4f CreateRotationZ(const float angle) noexcept;
        static Matrix4f CreateRotationZ(const float angle, const Vector3f& position) noexcept;
        static Matrix4f CreateScale(const float scale) noexcept;
        static Matrix4f CreateScale(const float scaleX, const float scaleY, const float scaleZ) noexcept;
        static Matrix4f CreateTranslation(const float translationX, const float translationY, const float translationZ) noexcept;
        static Matrix4f CreateTranslation(const Vector3f& translation) noexcept;
        static Matrix4f Lerp(const Matrix4f& firstMatrix, const Matrix4f& secondMatrix, const float t) noexcept;

        const std::vector<float> ToArray() const noexcept override;
        std::string ToString() const noexcept;
        std::string ToStringInline() const noexcept;

        void operator +=(const Matrix4f& matrix) noexcept;
        void operator -=(const Matrix4f& matrix) noexcept;
        void operator *=(const Matrix4f& matrix) noexcept;
        void operator *=(const float scalar) noexcept;
        void operator /=(const float scalar);
        Matrix4f operator -() const noexcept;
        float operator [](int index) const;
        float& operator [](int index);
    };
}

FaceEngine::Matrix4f operator +(const FaceEngine::Matrix4f& firstMatrix, const FaceEngine::Matrix4f& secondMatrix) noexcept;
FaceEngine::Matrix4f operator -(const FaceEngine::Matrix4f& firstMatrix, const FaceEngine::Matrix4f& secondMatrix) noexcept;
FaceEngine::Matrix4f operator *(const FaceEngine::Matrix4f& firstMatrix, const FaceEngine::Matrix4f& secondMatrix) noexcept;
FaceEngine::Matrix4f operator *(const FaceEngine::Matrix4f& matrix, const float scalar) noexcept;
FaceEngine::Matrix4f operator /(const FaceEngine::Matrix4f& matrix, const float scalar);
bool operator ==(const FaceEngine::Matrix4f& firstMatrix, const FaceEngine::Matrix4f& secondMatrix) noexcept;
bool operator !=(const FaceEngine::Matrix4f& firstMatrix, const FaceEngine::Matrix4f& secondMatrix) noexcept;

std::ostream& operator <<(std::ostream& cout, const FaceEngine::Matrix4f& matrix) noexcept;

#endif