#include "FaceEngine/Math/Matrix4f.h"
#include "FaceEngine/Math/Matrix3f.h"
#include <cmath>

FaceEngine::Matrix4f::Matrix4f()
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

FaceEngine::Matrix4f::Matrix4f(const FaceEngine::Matrix4f& matrix)
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

FaceEngine::Matrix4f::Matrix4f(const float& m11, const float& m12, const float& m13, const float& m14, const float& m21, const float& m22, const float& m23, const float& m24, const float& m31, const float& m32, const float& m33, const float& m34, const float& m41, const float& m42, const float& m43, const float& m44)
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

float FaceEngine::Matrix4f::GetDeterminant() const
{
    return M11 * (M22 * (M33 * M44 - M34 * M43) - M23 * (M32 * M44 - M34 * M42) + M24 * (M32 * M43 - M33 * M42))
                - M12 * (M21 * (M33 * M44 - M34 * M43) - M23 * (M31 * M44 - M34 * M41) + M24 * (M31 * M43 - M33 * M41))
                + M13 * (M21 * (M32 * M44 - M34 * M42) - M22 * (M31 * M44 - M34 * M41) + M24 * (M31 * M42 - M32 * M41))
                - M14 * (M21 * (M33 * M43 - M32 * M42) - M22 * (M31 * M43 - M32 * M41) + M23 * (M31 * M43 - M33 * M41));
}

FaceEngine::Matrix4f FaceEngine::Matrix4f::GetInverse() const
{
    Matrix4f adjoint = GetAdjoint();
    float determinant = GetDeterminant();

    if (determinant == 0)
    {
        // TODO: throw exception: "Matrix is not invertible as the determinant is zero."
    }

    adjoint.Multiply(1 / determinant);

    return adjoint;
}

FaceEngine::Matrix4f FaceEngine::Matrix4f::GetMinors() const
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

FaceEngine::Matrix4f FaceEngine::Matrix4f::GetCofactors() const
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

FaceEngine::Matrix4f FaceEngine::Matrix4f::GetAdjoint() const
{
    Matrix4f adjoint = GetCofactors();
    adjoint.Transpose();

    return adjoint;
}

void FaceEngine::Matrix4f::Transpose()
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

void FaceEngine::Matrix4f::Add(const FaceEngine::Matrix4f& matrix)
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

void FaceEngine::Matrix4f::Subtract(const FaceEngine::Matrix4f& matrix)
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

void FaceEngine::Matrix4f::Multiply(const FaceEngine::Matrix4f& matrix)
{
    FaceEngine::Matrix4f original = FaceEngine::Matrix4f(*this);

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

void FaceEngine::Matrix4f::Multiply(const float& scalar)
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

void FaceEngine::Matrix4f::Divide(const float& scalar)
{
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

FaceEngine::Vector3f FaceEngine::Matrix4f::TransformHomogeneous(const FaceEngine::Vector3f& vector) const
{
    Vector3f result = Vector3f();

    result.X = (vector.X * M11) + (vector.Y * M12) + (vector.Z * M13) + M14;
    result.Y = (vector.X * M21) + (vector.Y * M22) + (vector.Z * M23) + M24;
    result.Z = (vector.X * M31) + (vector.Y * M32) + (vector.Z * M33) + M34;

    return result;
}

FaceEngine::Matrix4f FaceEngine::Matrix4f::CreateTranslation(const float& xTranslation, const float& yTranslation, const float& zTranslation)
{
    return Matrix4f(1, 0, 0, xTranslation, 0, 1, 0, yTranslation, 0, 0, 1, zTranslation, 0, 0, 0, 1);
}

FaceEngine::Matrix4f FaceEngine::Matrix4f::CreateScale(const float& xScale, const float& yScale, const float& zScale)
{
    return Matrix4f(xScale, 0, 0, 0, 0, yScale, 0, 0, 0, 0, zScale, 0, 0, 0, 0, 1);
}

FaceEngine::Matrix4f FaceEngine::Matrix4f::CreateRotationX(const float& angle)
{
    return Matrix4f(1, 0, 0, 0, 0, cos(angle), -sin(angle), 0, 0, sin(angle), cos(angle), 0, 0, 0, 0, 1);
}

FaceEngine::Matrix4f FaceEngine::Matrix4f::CreateRotationY(const float& angle)
{
    return Matrix4f(cos(angle), 0, sin(angle), 0, 0, 1, 0, 0, - sin(angle), 0, cos(angle), 0, 0, 0, 0, 1);
}

FaceEngine::Matrix4f FaceEngine::Matrix4f::CreateRotationZ(const float& angle)
{
    return Matrix4f(cos(angle), -sin(angle), 0, 0, sin(angle), cos(angle), 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);
}

FaceEngine::Matrix4f FaceEngine::Matrix4f::CreatePerspective(const float& fieldOfView, const float& aspectRatio, const float& nearPlane, const float& farPlane)
{
    float yScale = 1 / tan(fieldOfView / 2);
    float xScale = yScale / aspectRatio;

    return Matrix4f(xScale, 0, 0, 0, 0, yScale, 0, 0, 0, 0, -farPlane / (farPlane - nearPlane), -1, 0, 0, -(farPlane * nearPlane) / (farPlane - nearPlane), 0);
}

FaceEngine::Matrix4f FaceEngine::Matrix4f::CreateOrthographic(const float& width, const float& height, const float& nearPlane, const float& farPlane)
{
    return Matrix4f(2 / width, 0, 0, -1, 0, -2 / height, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1);
}

const std::vector<float> FaceEngine::Matrix4f::ToArray() const noexcept
{
    return {M11, M21, M31, M41, M12, M22, M32, M42, M13, M23, M33, M43, M14, M24, M34, M44};
}

std::string FaceEngine::Matrix4f::ToString() const
{
    return "Matrix4: [" + std::to_string(M11) + " " + std::to_string(M12) + " " + std::to_string(M13) + " " + std::to_string(M14) + "\n "
            + std::to_string(M21) + " " + std::to_string(M22) + " " + std::to_string(M23) + " " + std::to_string(M24) + "\n "
            + std::to_string(M31) + " " + std::to_string(M32) + " " + std::to_string(M33) + " " + std::to_string(M34) + "\n "
            + std::to_string(M41) + " " + std::to_string(M42) + " " + std::to_string(M43) + " " + std::to_string(M44) + "]";
}

std::string FaceEngine::Matrix4f::ToStringInline() const
{
    return "Matrix4: [" + std::to_string(M11) + " " + std::to_string(M12) + " " + std::to_string(M13) + " " + std::to_string(M14) + " "
            + std::to_string(M21) + " " + std::to_string(M22) + " " + std::to_string(M23) + " " + std::to_string(M24) + " "
            + std::to_string(M31) + " " + std::to_string(M32) + " " + std::to_string(M33) + " " + std::to_string(M34) + " "
            + std::to_string(M41) + " " + std::to_string(M42) + " " + std::to_string(M43) + " " + std::to_string(M44) + "]";
}

void FaceEngine::Matrix4f::operator +=(const FaceEngine::Matrix4f& matrix)
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

void FaceEngine::Matrix4f::operator -=(const FaceEngine::Matrix4f& matrix)
{
    this->Add(matrix);
}

void FaceEngine::Matrix4f::operator *=(const FaceEngine::Matrix4f& matrix)
{
    this->Multiply(matrix);
}

void FaceEngine::Matrix4f::operator *=(const float& scalar)
{
    this->Multiply(scalar);
}

void FaceEngine::Matrix4f::operator /=(const float& scalar)
{
    this->Divide(scalar);
}

FaceEngine::Matrix4f FaceEngine::operator +(const FaceEngine::Matrix4f& firstMatrix, const FaceEngine::Matrix4f& secondMatrix)
{
    FaceEngine::Matrix4f result = FaceEngine::Matrix4f(firstMatrix);
    result.Add(secondMatrix);
    return result;
}

FaceEngine::Matrix4f FaceEngine::operator -(const FaceEngine::Matrix4f& firstMatrix, const FaceEngine::Matrix4f& secondMatrix)
{
    FaceEngine::Matrix4f result = FaceEngine::Matrix4f(firstMatrix);
    result.Subtract(secondMatrix);
    return result;
}

FaceEngine::Matrix4f FaceEngine::operator *(const FaceEngine::Matrix4f& firstMatrix, const FaceEngine::Matrix4f& secondMatrix)
{
    FaceEngine::Matrix4f result = FaceEngine::Matrix4f(firstMatrix);
    result.Multiply(secondMatrix);
    return result;
}

FaceEngine::Matrix4f FaceEngine::operator *(const FaceEngine::Matrix4f& firstMatrix, const float& scalar)
{
    FaceEngine::Matrix4f result = FaceEngine::Matrix4f(firstMatrix);
    result.Multiply(scalar);
    return result;
}

FaceEngine::Matrix4f FaceEngine::operator /(const FaceEngine::Matrix4f& firstMatrix, const float& scalar)
{
    FaceEngine::Matrix4f result = FaceEngine::Matrix4f(firstMatrix);
    result.Divide(scalar);
    return result;
}

std::ostream& FaceEngine::operator <<(std::ostream& cout, const FaceEngine::Matrix4f& matrix)
{
    cout << matrix.ToStringInline();
    return cout;
}