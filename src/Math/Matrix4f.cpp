#include "FaceEngine/Math/Matrix4f.h"
#include "FaceEngine/Math/Matrix3f.h"
#include <cmath>

namespace FaceEngine
{
    const Matrix4f Matrix4f::Zero = Matrix4f(0, 0, 0, 0, 
                                             0, 0, 0, 0, 
                                             0, 0, 0, 0, 
                                             0, 0, 0, 0);
    const Matrix4f Matrix4f::Identity = Matrix4f(1, 0, 0, 0,
                                                 0, 1, 0, 0,
                                                 0, 0, 1, 0,
                                                 0, 0, 0, 1);

    Matrix4f::Matrix4f() noexcept
    {
        M11 = 0;
        M12 = 0;
        M13 = 0;
        M14 = 0;
        M21 = 0;
        M22 = 0;
        M23 = 0;
        M24 = 0;
        M31 = 0;
        M32 = 0;
        M33 = 0;
        M34 = 0;
        M41 = 0;
        M42 = 0;
        M43 = 0;
        M44 = 0;
    }

    Matrix4f::Matrix4f(const Matrix4f& matrix) noexcept
    {
        M11 = matrix.M11;
        M12 = matrix.M12;
        M13 = matrix.M13;
        M14 = matrix.M14;
        M21 = matrix.M21;
        M22 = matrix.M22;
        M23 = matrix.M23;
        M24 = matrix.M24;
        M31 = matrix.M31;
        M32 = matrix.M32;
        M33 = matrix.M33;
        M34 = matrix.M34;
        M41 = matrix.M41;
        M42 = matrix.M42;
        M43 = matrix.M43;
        M44 = matrix.M44;
    }

    Matrix4f::Matrix4f(const float m11, const float m12, const float m13, const float m14, 
                       const float m21, const float m22, const float m23, const float m24, 
                       const float m31, const float m32, const float m33, const float m34, 
                       const float m41, const float m42, const float m43, const float m44) noexcept
    {
        M11 = m11;
        M12 = m12;
        M13 = m13;
        M14 = m14;
        M21 = m21;
        M22 = m22;
        M23 = m23;
        M24 = m24;
        M31 = m31;
        M32 = m32;
        M33 = m33;
        M34 = m34;
        M41 = m41;
        M42 = m42;
        M43 = m43;
        M44 = m44;
    }

    Matrix4f::Matrix4f(const Vector3f& rightVector, const Vector3f& upVector, const Vector3f& forwardVector, const Vector3f& translation) noexcept
    {
        M11 = rightVector.X;
        M21 = rightVector.Y;
        M31 = rightVector.Z;
        
        M12 = upVector.X;
        M22 = upVector.Y;
        M32 = upVector.Z;

        M13 = forwardVector.X;
        M23 = forwardVector.Y;
        M33 = forwardVector.Z;

        M14 = translation.X;
        M24 = translation.Y;
        M34 = translation.Z;

        M41 = 0;
        M42 = 0;
        M43 = 0;
        M44 = 1;
    }

    float Matrix4f::GetDeterminant() const noexcept
    {
        return M11 * (M22 * (M33 * M44 - M34 * M43) - M23 * (M32 * M44 - M34 * M42) + M24 * (M32 * M43 - M33 * M42))
                    - M12 * (M21 * (M33 * M44 - M34 * M43) - M23 * (M31 * M44 - M34 * M41) + M24 * (M31 * M43 - M33 * M41))
                    + M13 * (M21 * (M32 * M44 - M34 * M42) - M22 * (M31 * M44 - M34 * M41) + M24 * (M31 * M42 - M32 * M41))
                    - M14 * (M21 * (M33 * M43 - M32 * M42) - M22 * (M31 * M43 - M32 * M41) + M23 * (M31 * M43 - M33 * M41));
    }

    Matrix4f Matrix4f::GetInverse() const
    {
        Matrix4f adjoint = GetAdjoint();
        float determinant = GetDeterminant();

        if (determinant == 0)
        {
            throw Exception::FromMessage("Matrix4f::GetInverse()", "Matrix4f is not invertible as the determinant is zero.");
        }

        adjoint *= 1 / determinant;

        return adjoint;
    }

    Matrix4f Matrix4f::GetMinors() const noexcept
    {
        Matrix4f minors;

        minors.M11 = Matrix3f(M22, M23, M24, M32, M33, M34, M42, M43, M44).GetDeterminant();
        minors.M12 = Matrix3f(M21, M23, M24, M31, M33, M34, M41, M43, M33).GetDeterminant();
        minors.M13 = Matrix3f(M21, M22, M24, M31, M32, M34, M41, M42, M44).GetDeterminant();
        minors.M14 = Matrix3f(M21, M22, M23, M31, M32, M33, M41, M42, M43).GetDeterminant();
        minors.M21 = Matrix3f(M12, M13, M14, M32, M33, M34, M42, M43, M44).GetDeterminant();
        minors.M22 = Matrix3f(M11, M13, M14, M31, M33, M34, M41, M43, M44).GetDeterminant();
        minors.M23 = Matrix3f(M11, M12, M14, M31, M32, M34, M41, M42, M44).GetDeterminant();
        minors.M24 = Matrix3f(M11, M12, M13, M31, M32, M33, M41, M42, M43).GetDeterminant();
        minors.M31 = Matrix3f(M12, M13, M14, M22, M23, M24, M42, M43, M44).GetDeterminant();
        minors.M32 = Matrix3f(M11, M13, M14, M21, M23, M24, M41, M43, M44).GetDeterminant();
        minors.M33 = Matrix3f(M11, M12, M14, M21, M22, M24, M41, M42, M44).GetDeterminant();
        minors.M34 = Matrix3f(M11, M12, M13, M21, M22, M23, M41, M42, M43).GetDeterminant();
        minors.M41 = Matrix3f(M12, M13, M14, M22, M23, M24, M32, M33, M34).GetDeterminant();
        minors.M42 = Matrix3f(M11, M13, M14, M21, M23, M24, M31, M33, M34).GetDeterminant();
        minors.M43 = Matrix3f(M11, M12, M14, M21, M22, M24, M31, M32, M34).GetDeterminant();
        minors.M44 = Matrix3f(M11, M12, M13, M21, M22, M23, M31, M32, M33).GetDeterminant();

        return minors;
    }

    Matrix4f Matrix4f::GetCofactors() const noexcept
    {
        Matrix4f cofactors = GetMinors();

        cofactors.M12 *= -1;
        cofactors.M14 *= -1;
        cofactors.M21 *= -1;
        cofactors.M23 *= -1;
        cofactors.M32 *= -1;
        cofactors.M34 *= -1;
        cofactors.M41 *= -1;
        cofactors.M43 *= -1;

        return cofactors;
    }

    Matrix4f Matrix4f::GetAdjoint() const noexcept
    {
        Matrix4f adjoint = GetCofactors();
        adjoint.Transpose();

        return adjoint;
    }

    bool Matrix4f::Equals(Matrix4f& matrix) const noexcept
    {
        return M11 == matrix.M11 && M12 == matrix.M12 && M13 == matrix.M13 && M14 == matrix.M14 &&
               M21 == matrix.M21 && M22 == matrix.M22 && M23 == matrix.M23 && M24 == matrix.M24 &&
               M31 == matrix.M31 && M32 == matrix.M32 && M33 == matrix.M33 && M34 == matrix.M34 &&
               M41 == matrix.M41 && M42 == matrix.M42 && M43 == matrix.M43 && M44 == matrix.M44;
    }

    void Matrix4f::Transpose() noexcept
    {
        float tempM12 = M12;
        float tempM13 = M13;
        float tempM14 = M14;
        float tempM23 = M23;
        float tempM24 = M24;
        float tempM34 = M34;

        M12 = M21;
        M13 = M31;
        M14 = M41;
        M23 = M32;
        M24 = M42;
        M34 = M43;

        M21 = tempM12;
        M31 = tempM13;
        M41 = tempM14;
        M32 = tempM23;
        M42 = tempM24;
        M43 = tempM34;
    }

    void Matrix4f::Add(const Matrix4f& matrix) noexcept
    {
        M11 += matrix.M11;
        M12 += matrix.M12;
        M13 += matrix.M13;
        M14 += matrix.M14;
        M21 += matrix.M21;
        M22 += matrix.M22;
        M23 += matrix.M23;
        M24 += matrix.M24;
        M31 += matrix.M31;
        M32 += matrix.M32;
        M33 += matrix.M33;
        M34 += matrix.M34;
        M41 += matrix.M41;
        M42 += matrix.M42;
        M43 += matrix.M43;
        M44 += matrix.M44;
    }

    void Matrix4f::Subtract(const Matrix4f& matrix) noexcept
    {
        M11 -= matrix.M11;
        M12 -= matrix.M12;
        M13 -= matrix.M13;
        M14 -= matrix.M14;
        M21 -= matrix.M21;
        M22 -= matrix.M22;
        M23 -= matrix.M23;
        M24 -= matrix.M24;
        M31 -= matrix.M31;
        M32 -= matrix.M32;
        M33 -= matrix.M33;
        M34 -= matrix.M34;
        M41 -= matrix.M41;
        M42 -= matrix.M42;
        M43 -= matrix.M43;
        M44 -= matrix.M44;
    }

    void Matrix4f::Multiply(const Matrix4f& matrix) noexcept
    {
        Matrix4f original = Matrix4f(*this);

        M11 = original.M11 * matrix.M11 + original.M12 * matrix.M21 + original.M13 * matrix.M31
                    + original.M14 * matrix.M41;
        M12 = original.M11 * matrix.M12 + original.M12 * matrix.M22 + original.M13 * matrix.M32
                + original.M14 * matrix.M42;
        M13 = original.M11 * matrix.M13 + original.M12 * matrix.M23 + original.M13 * matrix.M33
                + original.M14 * matrix.M43;
        M14 = original.M11 * matrix.M14 + original.M12 * matrix.M24 + original.M13 * matrix.M34
                + original.M14 * matrix.M44;
        M21 = original.M21 * matrix.M11 + original.M22 * matrix.M21 + original.M23 * matrix.M31
                + original.M24 * matrix.M41;
        M22 = original.M21 * matrix.M12 + original.M22 * matrix.M22 + original.M23 * matrix.M32
                + original.M24 * matrix.M42;
        M23 = original.M21 * matrix.M13 + original.M22 * matrix.M23 + original.M23 * matrix.M33
                + original.M24 * matrix.M43;
        M24 = original.M21 * matrix.M14 + original.M22 * matrix.M24 + original.M23 * matrix.M34
                + original.M24 * matrix.M44;
        M31 = original.M31 * matrix.M11 + original.M32 * matrix.M21 + original.M33 * matrix.M31
                + original.M34 * matrix.M41;
        M32 = original.M31 * matrix.M12 + original.M32 * matrix.M22 + original.M33 * matrix.M32
                + original.M34 * matrix.M42;
        M33 = original.M31 * matrix.M13 + original.M32 * matrix.M23 + original.M33 * matrix.M33
                + original.M34 * matrix.M43;
        M34 = original.M31 * matrix.M14 + original.M32 * matrix.M24 + original.M33 * matrix.M34
                + original.M34 * matrix.M44;
        M41 = original.M41 * matrix.M11 + original.M42 * matrix.M21 + original.M43 * matrix.M31
                + original.M44 * matrix.M41;
        M42 = original.M41 * matrix.M12 + original.M42 * matrix.M22 + original.M43 * matrix.M32
                + original.M44 * matrix.M42;
        M43 = original.M41 * matrix.M13 + original.M42 * matrix.M23 + original.M43 * matrix.M33
                + original.M44 * matrix.M43;
        M44 = original.M41 * matrix.M14 + original.M42 * matrix.M24 + original.M43 * matrix.M34
                + original.M44 * matrix.M44;
    }

    void Matrix4f::Multiply(const float scalar) noexcept
    {
        M11 *= scalar;
        M12 *= scalar;
        M13 *= scalar;
        M14 *= scalar;
        M21 *= scalar;
        M22 *= scalar;
        M23 *= scalar;
        M24 *= scalar;
        M31 *= scalar;
        M32 *= scalar;
        M33 *= scalar;
        M34 *= scalar;
        M41 *= scalar;
        M42 *= scalar;
        M43 *= scalar;
        M44 *= scalar;
    }

    void Matrix4f::Divide(const float scalar)
    {
        if (scalar == 0)
        {
            throw Exception::FromMessage("Matrix4f::Divide", "Divisor cannot be zero.");
        }

        M11 /= scalar;
        M12 /= scalar;
        M13 /= scalar;
        M14 /= scalar;
        M21 /= scalar;
        M22 /= scalar;
        M23 /= scalar;
        M24 /= scalar;
        M31 /= scalar;
        M32 /= scalar;
        M33 /= scalar;
        M34 /= scalar;
        M41 /= scalar;
        M42 /= scalar;
        M43 /= scalar;
        M44 /= scalar;
    }

    void Matrix4f::Transform(Vector3f& vector) const noexcept
    {
        float oldX = vector.X;
        float oldY = vector.Y;

        vector.X = vector.X * M11 + vector.Y * M12 + vector.Z * M13 + M14;
        vector.Y = oldX * M21 + vector.Y * M22 + vector.Z * M23 + M24;
        vector.Z = oldX * M31 + oldY * M32 + vector.Z * M33 + M34;
    }

    void Matrix4f::Transform(Vector4f& vector) const noexcept
    {
        float oldX = vector.X;
        float oldY = vector.Y;
        float oldZ = vector.Z;

        vector.X = vector.X * M11 + vector.Y * M12 + vector.Z * M13 + vector.W * M14;
        vector.Y = oldX * M21 + vector.Y * M22 + vector.Z * M23 + vector.W * M24;
        vector.Z = oldX * M31 + oldY * M32 + vector.Z * M33 + vector.W * M34;
        vector.W = oldZ * M41 + oldY * M42 + oldZ * M43 + vector.W * M44;
    }

    void Matrix4f::SetRight(const Vector3f& rightVector) noexcept
    {
        M11 = rightVector.X;
        M21 = rightVector.Y;
        M31 = rightVector.Z;
    }

    void Matrix4f::SetUp(const Vector3f& upVector) noexcept
    {
        M12 = upVector.X;
        M22 = upVector.Y;
        M32 = upVector.Z;
    }

    void Matrix4f::SetForward(const Vector3f& forwardVector) noexcept
    {
        M13 = forwardVector.X;
        M23 = forwardVector.Y;
        M33 = forwardVector.Z;
    }

    void Matrix4f::SetTranslation(const float translationX, const float translationY, const float translationZ) noexcept
    {
        M14 = translationX;
        M24 = translationY;
        M34 = translationZ;
    }

    void Matrix4f::SetTranslation(const Vector3f& translation) noexcept
    {
        M14 = translation.X;
        M24 = translation.Y;
        M34 = translation.Z;
    }

    void Matrix4f::SetScale(const float scale) noexcept
    {
        M11 = scale;
        M22 = scale;
        M33 = scale;
    }

    void Matrix4f::SetScale(const float scaleX, const float scaleY, const float scaleZ) noexcept
    {
        M11 = scaleX;
        M22 = scaleY;
        M33 = scaleZ;
    }

    Vector3f Matrix4f::GetRight() const noexcept
    {
        return Vector3f(M11, M21, M31);
    }

    Vector3f Matrix4f::GetUp() const noexcept
    {
        return Vector3f(M21, M22, M23);
    }

    Vector3f Matrix4f::GetForward() const noexcept
    {
        return Vector3f(M31, M32, M33);
    }
    
    Vector3f Matrix4f::GetTranslation() const noexcept
    {
        return Vector3f(M14, M24, M34);
    }

    Vector3f Matrix4f::GetScale() const noexcept
    {
        return Vector3f(M11, M22, M33);
    }

    Matrix4f Matrix4f::CreateBillboard(Vector3f& objectPos, Vector3f& cameraPos, Vector3f& upVector, Vector3f& forwardVector) noexcept
    {
        // TODO: implement
        return Identity;
    }

    Matrix4f Matrix4f::CreateConstrainedBillboard(Vector3f& objectPos, Vector3f& cameraPos, Vector3f& upVector, Vector3f& forwardVector, Vector3f& rotationAxis) noexcept
    {
        // TODO: implement
        return Identity;
    }

    // moves everything such that the camera is at the origin and is facing -Z axis.
    Matrix4f Matrix4f::CreateLookAt(Vector3f& cameraPos, Vector3f& targetPos, Vector3f& upVector) noexcept
    {
        // this won't work as Monogame is the wrong major

        Matrix4f matrix = Matrix4f::Identity;

        float x[3];
        float y[3];
        float z[3];

        z[0] = cameraPos.X - targetPos.X;
        z[1] = cameraPos.Y - targetPos.Y;
        z[2] = cameraPos.Z - targetPos.Z;
        float mag = sqrtf((z[0] * z[0] + z[1] * z[1] + z[2] * z[2]));

        if (mag > 0)
        {
            z[0] /= mag;
            z[1] /= mag;
            z[2] /= mag;
        }

        x[0] = upVector.Y * z[2] - upVector.Z * z[1];
        x[1] = -upVector.X * z[2] + upVector.Z * z[0];
        x[2] = upVector.X * z[1] - upVector.Y * z[0];

        y[0] = z[1] * x[2] - z[2] * x[1];
        y[1] = -z[0] * x[2] + z[2] * x[0];
        y[2] = z[0] * x[1] - z[1] * x[0];

        mag = sqrtf(x[0] * x[0] + x[1] * x[1] + x[2] * x[2]);

        if (mag > 0)
        {
            y[0] /= mag;
            y[1] /= mag;
            y[2] /= mag;
        }

        matrix.M11 = x[0];
        matrix.M12 = x[1];
        matrix.M13 = x[2];
        matrix.M14 = 0.0f;
        matrix.M21 = y[0];
        matrix.M22 = y[1];
        matrix.M23 = y[2];
        matrix.M24 = 0.0f;
        matrix.M31 = z[0];
        matrix.M32 = z[1];
        matrix.M33 = z[2];
        matrix.M34 = 0.0f;
        matrix.M41 = 0.0f;
        matrix.M42 = 0.0f;
        matrix.M43 = 0.0f;
        matrix.M44 = 1.0f;

        return matrix;
    }

    Matrix4f Matrix4f::CreateOrthographic(const float width, const float height, const float zNearPlane, const float zFarPlane) noexcept
    {
        return Matrix4f(2 / width, 0, 0, -1,
                        0, -2 / height, 0, 1, 
                        0, 0, 1, 0, 
                        0, 0, 0, 1);
    }

    Matrix4f Matrix4f::CreateOrthographicOffCentre(const float left, const float right, const float bottom, const float top, const float zNearPlane, const float zFarPlane) noexcept
    {
        // TODO: implement
        return Identity;
    }

    Matrix4f Matrix4f::CreatePerspective(const float width, const float height, const float nearPlaneDistance, const float farPlaneDistance) noexcept
    {
        // TODO: implement
        return Identity;
    }

    Matrix4f Matrix4f::CreatePerspectiveFOV(const float fieldOfView, const float aspectRatio, const float nearPlane, const float farPlane) noexcept
    {
        float yScale = 1 / tan(fieldOfView / 2);
        float xScale = yScale / aspectRatio;

        return Matrix4f(xScale, 0, 0, 0, 0, yScale, 0, 0, 0, 0, -farPlane / (farPlane - nearPlane), -1, 0, 0, -(farPlane * nearPlane) / (farPlane - nearPlane), 0);
    }

    Matrix4f Matrix4f::CreatePerspectiveOffCentre(const float left, const float right, const float bottom, const float top, const float nearPlaneDistance, const float farPlaneDistance) noexcept
    {
        // TODO: implement
        return Identity;
    }

    Matrix4f Matrix4f::CreateWorld(const Vector3f& objectPos, const Vector3f& upVector, const Vector3f& forwardVector) noexcept
    {
        Vector3f rightVector = upVector.Cross(forwardVector);

        return Matrix4f(rightVector.X, upVector.X, forwardVector.X, objectPos.X,
                        rightVector.Y, upVector.Y, forwardVector.Y, objectPos.Y,
                        rightVector.Z, upVector.Z, forwardVector.Z, objectPos.Z,
                        0, 0, 0, 1);
    }

    Matrix4f Matrix4f::CreateRotationX(const float angle) noexcept
    {
        return Matrix4f(1, 0, 0, 0, 0, cos(angle), -sin(angle), 0, 0, sin(angle), cos(angle), 0, 0, 0, 0, 1);
    }

    Matrix4f Matrix4f::CreateRotationX(const float angle, const Vector3f& position) noexcept
    {
        // TODO: implement
        return Identity;
    }

    Matrix4f Matrix4f::CreateRotationY(const float angle) noexcept
    {
        return Matrix4f(cos(angle), 0, sin(angle), 0, 0, 1, 0, 0, - sin(angle), 0, cos(angle), 0, 0, 0, 0, 1);
    }

    Matrix4f Matrix4f::CreateRotationY(const float angle, const Vector3f& position) noexcept
    {
        // TODO: implement
        return Identity;
    }

    Matrix4f Matrix4f::CreateRotationZ(const float angle) noexcept
    {
        return Matrix4f(cos(angle), -sin(angle), 0, 0, sin(angle), cos(angle), 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);
    }

    Matrix4f Matrix4f::CreateRotationZ(const float angle, const Vector3f& position) noexcept
    {
        // TODO: implement
        return Identity;
    }
    
    Matrix4f Matrix4f::CreateScale(const float scale) noexcept
    {
        return Matrix4f(scale, 0, 0, 0, 0, scale, 0, 0, 0, 0, scale, 0, 0, 0, 0, 1);
    }

    Matrix4f Matrix4f::CreateScale(const float scaleX, const float scaleY, const float scaleZ) noexcept
    {
        return Matrix4f(scaleX, 0, 0, 0, 0, scaleY, 0, 0, 0, 0, scaleZ, 0, 0, 0, 0, 1);
    }

    Matrix4f Matrix4f::CreateTranslation(const float translationX, const float translationY, const float translationZ) noexcept
    {
        return Matrix4f(1, 0, 0, translationX, 0, 1, 0, translationY, 0, 0, 1, translationZ, 0, 0, 0, 1);
    }

    Matrix4f Matrix4f::CreateTranslation(const Vector3f& translation) noexcept
    {
        return Matrix4f(1, 0, 0, translation.X, 0, 1, 0, translation.Y, 0, 0, 1, translation.Z, 0, 0, 0, 1);
    }

    Matrix4f Matrix4f::Lerp(const Matrix4f& firstMatrix, const Matrix4f& secondMatrix, const float t) noexcept
    {
        // TODO: implement (https://stackoverflow.com/questions/27751602/interpolation-between-2-4x4-matrices)
        return Identity;
    }

    const std::vector<float> Matrix4f::ToArray() const noexcept
    {
        return {M11, M21, M31, M41, M12, M22, M32, M42, M13, M23, M33, M43, M14, M24, M34, M44};
    }

    std::string Matrix4f::ToString() const noexcept
    {
        return "Matrix4: [" + std::to_string(M11) + " " + std::to_string(M12) + " " + std::to_string(M13) + " " + std::to_string(M14) + "\n "
                + std::to_string(M21) + " " + std::to_string(M22) + " " + std::to_string(M23) + " " + std::to_string(M24) + "\n "
                + std::to_string(M31) + " " + std::to_string(M32) + " " + std::to_string(M33) + " " + std::to_string(M34) + "\n "
                + std::to_string(M41) + " " + std::to_string(M42) + " " + std::to_string(M43) + " " + std::to_string(M44) + "]";
    }

    std::string Matrix4f::ToStringInline() const noexcept
    {
        return "Matrix4: [" + std::to_string(M11) + " " + std::to_string(M12) + " " + std::to_string(M13) + " " + std::to_string(M14) + " "
                + std::to_string(M21) + " " + std::to_string(M22) + " " + std::to_string(M23) + " " + std::to_string(M24) + " "
                + std::to_string(M31) + " " + std::to_string(M32) + " " + std::to_string(M33) + " " + std::to_string(M34) + " "
                + std::to_string(M41) + " " + std::to_string(M42) + " " + std::to_string(M43) + " " + std::to_string(M44) + "]";
    }

    void Matrix4f::operator +=(const Matrix4f& matrix) noexcept
    {
        Add(matrix);
    }

    void Matrix4f::operator -=(const Matrix4f& matrix) noexcept
    {
        Subtract(matrix);
    }

    void Matrix4f::operator *=(const Matrix4f& matrix) noexcept
    {
        Multiply(matrix);
    }

    void Matrix4f::operator *=(const float scalar) noexcept
    {
        Multiply(scalar);
    }

    void Matrix4f::operator /=(const float scalar)
    {
        // Error checking handled in Matrix4f::Divide()

        Divide(scalar);
    }

    Matrix4f Matrix4f::operator -() const noexcept
    {
        Matrix4f matrix = Matrix4f(*this);
        matrix.Multiply(-1);

        return matrix;
    }

    float Matrix4f::operator [](int index) const
    {
        if (index < 0 || index > 15)
        {
            throw Exception::FromMessage("Matrix4f::operator[](int)", "Index out of bounds of Matrix4f.");
        }

        switch (index)
        {
            case 0: return M11;
            case 1: return M12;
            case 2: return M13;
            case 3: return M14;
            case 4: return M21;
            case 5: return M22;
            case 6: return M23;
            case 7: return M24;
            case 8: return M31;
            case 9: return M32;
            case 10: return M33;
            case 11: return M34;
            case 12: return M41;
            case 13: return M42;
            case 14: return M43;
            case 15: return M44;
        }
    }

    float& Matrix4f::operator [](int index)
    {
        if (index < 0 || index > 15)
        {
            throw Exception::FromMessage("Matrix4f::operator[](int)", "Index out of bounds of Matrix4f.");
        }

        switch (index)
        {
            case 0: return M11;
            case 1: return M12;
            case 2: return M13;
            case 3: return M14;
            case 4: return M21;
            case 5: return M22;
            case 6: return M23;
            case 7: return M24;
            case 8: return M31;
            case 9: return M32;
            case 10: return M33;
            case 11: return M34;
            case 12: return M41;
            case 13: return M42;
            case 14: return M43;
            case 15: return M44;
        }
    }
}

FaceEngine::Matrix4f operator +(const FaceEngine::Matrix4f& firstMatrix, const FaceEngine::Matrix4f& secondMatrix) noexcept
{
    FaceEngine::Matrix4f result = FaceEngine::Matrix4f(firstMatrix);
    result.Add(secondMatrix);
    return result;
}

FaceEngine::Matrix4f operator -(const FaceEngine::Matrix4f& firstMatrix, const FaceEngine::Matrix4f& secondMatrix) noexcept
{
    FaceEngine::Matrix4f result = FaceEngine::Matrix4f(firstMatrix);
    result.Subtract(secondMatrix);
    return result;
}

FaceEngine::Matrix4f operator *(const FaceEngine::Matrix4f& firstMatrix, const FaceEngine::Matrix4f& secondMatrix) noexcept
{
    FaceEngine::Matrix4f result = FaceEngine::Matrix4f(firstMatrix);
    result.Multiply(secondMatrix);
    return result;
}

FaceEngine::Vector3f operator *(const FaceEngine::Matrix4f& matrix, const FaceEngine::Vector3f& vector) noexcept
{
    return FaceEngine::Vector3f(vector.X * matrix.M11 + vector.Y * matrix.M12 + vector.Z * matrix.M13 + matrix.M14,
                                vector.X * matrix.M21 + vector.Y * matrix.M22 + vector.Z * matrix.M23 + matrix.M24,
                                vector.X * matrix.M31 + vector.Y * matrix.M32 + vector.Z * matrix.M33 + matrix.M34);
}

FaceEngine::Vector4f operator *(const FaceEngine::Matrix4f& matrix, const FaceEngine::Vector4f& vector) noexcept
{
    return FaceEngine::Vector4f(vector.X * matrix.M11 + vector.Y * matrix.M12 + vector.Z * matrix.M13 + vector.W * matrix.M14,
                                vector.X * matrix.M21 + vector.Y * matrix.M22 + vector.Z * matrix.M23 + vector.W * matrix.M24,
                                vector.X * matrix.M31 + vector.Y * matrix.M32 + vector.Z * matrix.M33 + vector.W * matrix.M34,
                                vector.X * matrix.M41 + vector.Y * matrix.M42 + vector.Z * matrix.M43 + vector.W * matrix.M44);
}

FaceEngine::Matrix4f operator *(const FaceEngine::Matrix4f& firstMatrix, const float& scalar) noexcept
{
    FaceEngine::Matrix4f result = FaceEngine::Matrix4f(firstMatrix);
    result.Multiply(scalar);
    return result;
}

FaceEngine::Matrix4f operator /(const FaceEngine::Matrix4f& firstMatrix, const float& scalar)
{
    FaceEngine::Matrix4f result = FaceEngine::Matrix4f(firstMatrix);
    result.Divide(scalar);
    return result;
}

bool operator ==(const FaceEngine::Matrix4f& firstMatrix, const FaceEngine::Matrix4f& secondMatrix) noexcept
{
    return firstMatrix.M11 == secondMatrix.M11 && firstMatrix.M12 == secondMatrix.M12 &&
           firstMatrix.M13 == secondMatrix.M13 && firstMatrix.M14 == secondMatrix.M14 &&
           firstMatrix.M21 == secondMatrix.M21 && firstMatrix.M22 == secondMatrix.M22 &&
           firstMatrix.M23 == secondMatrix.M23 && firstMatrix.M24 == secondMatrix.M24 &&
           firstMatrix.M31 == secondMatrix.M31 && firstMatrix.M32 == secondMatrix.M32 &&
           firstMatrix.M33 == secondMatrix.M33 && firstMatrix.M34 == secondMatrix.M34 &&
           firstMatrix.M41 == secondMatrix.M41 && firstMatrix.M42 == secondMatrix.M42 &&
           firstMatrix.M43 == secondMatrix.M43 && firstMatrix.M44 == secondMatrix.M44;
}

bool operator !=(const FaceEngine::Matrix4f& firstMatrix, const FaceEngine::Matrix4f& secondMatrix) noexcept
{
    return !(firstMatrix == secondMatrix);
}

std::ostream& operator <<(std::ostream& cout, const FaceEngine::Matrix4f& matrix) noexcept
{
    cout << matrix.ToStringInline();
    return cout;
}