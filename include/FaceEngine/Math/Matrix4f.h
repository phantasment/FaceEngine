#ifndef FACEENGINE_MATH_MATRIX4F_H_
#define FACEENGINE_MATH_MATRIX4F_H_

#include "FaceEngine/Math/Matrix.h"
#include "FaceEngine/Math/Vector3.h"
#include "FaceEngine/Math/Vector4.h"

namespace FaceEngine
{
    /**
     * @brief A 4x4 floating-point matrix.
     * 
     */
    class Matrix4f : public Matrix
    {
    public:
        /**
         * @brief A matrix element in the form [row][column] (row major).
         */
        float M11, M12, M13, M14, M21, M22, M23, M24, M31, M32, M33, M34, M41, M42, M43, M44;

        /**
         * @brief The zero matrix, a Matrix4f filled with zeroes.
         */
        static const Matrix4f Zero;

        /**
         * @brief The 4x4 identity matrix, a Matrix4f with ones along the primary diagonal.
         */
        static const Matrix4f Identity;

        /**
         * @brief Constructs a new Matrix4f object filled with zeroes.
         */
        Matrix4f() noexcept;

        /**
         * @brief Constructs a new Matrix4f object with the same values as the Matrix4f provided.
         * 
         * @param matrix The Matrix4f to source values from.
         */
        Matrix4f(const Matrix4f& matrix) noexcept;

        /**
         * @brief Constructs a new Matrix4f object with the values provided.
         * 
         * @param m11 The value at the first column of the first row.
         * @param m12 The value at the second column of the first row.
         * @param m13 The value at the third column of the first row. 
         * @param m14 The value at the fourth column of the first row.
         * @param m21 The value at the first column of the second row.
         * @param m22 The value at the second column of the second row.
         * @param m23 The value at the third column of the second row.
         * @param m24 The value at the fourth column of the second row.
         * @param m31 The value at the first column of the third row.
         * @param m32 The value at the second column of the third row.
         * @param m33 The value at the third column of the third row.
         * @param m34 The value at the fourth column of the third row.
         * @param m41 The value at the first column of the fourth row.
         * @param m42 The value at the second column of the fourth row.
         * @param m43 The value at the third column of the fourth row.
         * @param m44 The value at the fourth column of the fourth row.
         */
        Matrix4f(const float m11, const float m12, const float m13, const float m14, 
                 const float m21, const float m22, const float m23, const float m24, 
                 const float m31, const float m32, const float m33, const float m34, 
                 const float m41, const float m42, const float m43, const float m44) noexcept;
        
        /**
         * @brief Constructs a new Matrix4f object as a change-of-basis transition matrix plus a translation vector for homogeneous transformation.
         * 
         * @param rightVector The i-hat basis Vector3f (right vector).
         * @param upVector The j-hat basis Vector3f (up vector).
         * @param forwardVector The k-hat basis Vector3f (forward vector).
         * @param translation A Vector3f representing translation for homogeneous transformation.
         */
        Matrix4f(const Vector3f& rightVector, const Vector3f& upVector, const Vector3f& forwardVector, const Vector3f& translation) noexcept;

        /**
         * @brief Calculates the determinant of this Matrix4f.
         * 
         * @return The determinant as a float.
         */
        float GetDeterminant() const noexcept;

        /**
         * @brief Calculates the inverse of this Matrix4f.
         * 
         * @throws Exception throws when the determinant is zero.
         * @return The inverse Matrix4f.
         */
        Matrix4f GetInverse() const;

        /**
         * @brief Calculates a Matrix4f of the determinants of all minor matrices. Each element in the returned Matrix4f corresponds to the determinant of 
         * the minor matrix made up of the rows and columns it itself does not occupy.
         * 
         * @return A Matrix4f of minor matrix determinants.
         */
        Matrix4f GetMinors() const noexcept;

        /**
         * @brief Calculates the cofactors of this Matrix4f.
         * 
         * @return The Matrix4f of cofactors.
         */
        Matrix4f GetCofactors() const noexcept;

        /**
         * @brief Calculates the adjoint of this Matrix4f (the transpose of the cofactor matrix).
         * 
         * @return The adjoint Matrix4f.
         */
        Matrix4f GetAdjoint() const noexcept;

        /**
         * @brief Compares this Matrix4f with the provided Matrix4f to check if they are equal (element-wise).
         * 
         * @param matrix The Matrix4f to compare.
         * @return A boolean value representing whether or not the provided Matrix4f is equal to this one.
         */
        bool Equals(Matrix4f& matrix) const noexcept;

        /**
         * @brief Transposes this Matrix4f by flipping all elements across the primary diagonal.
         */
        void Transpose() noexcept;

        /**
         * @brief Adds the provided Matrix4f to this one.
         * 
         * @param matrix The Matrix4f to add.
         */
        void Add(const Matrix4f& matrix) noexcept;

        /**
         * @brief Subtracts the provided Matrix4f from this one.
         * 
         * @param matrix The Matrix4f to subtract.
         */
        void Subtract(const Matrix4f& matrix) noexcept;

        /**
         * @brief Multiplies the provided Matrix4f with this one.
         * 
         * @param matrix The Matrix4f to multiply.
         */
        void Multiply(const Matrix4f& matrix) noexcept;

        /**
         * @brief Multiplies each element of this Matrix4f by the provided scalar.
         * 
         * @param scalar The scalar to multiply the elements of this Matrix4f by.
         */
        void Multiply(const float scalar) noexcept;

        /**
         * @brief Divides each element of this Matrix4f by the provided scalar.
         * 
         * @throws Exception throws when the provided scalar is zero.
         * @param scalar The scalar to divide the elements of this Matrix4f by.
         */
        void Divide(const float scalar);

        void Transform(Vector3f& vector) const noexcept;
        void Transform(Vector4f& vector) const noexcept;

        /**
         * @brief Sets the i-hat basis Vector3f of this Matrix4f, i.e., elements M11, M21, and M31.
         * 
         * @param rightVector The i-hat basis Vector3f to set.
         */
        void SetRight(const Vector3f& rightVector) noexcept;

        /**
         * @brief Sets the j-hat basis Vector3f of this Matrix4f, i.e., elements M12, M22, and M32.
         * 
         * @param upVector The j-hat basis Vector3f to set.
         */
        void SetUp(const Vector3f& upVector) noexcept;

        /**
         * @brief Sets the k-hat basis Vector3f of this Matrix4f, i.e., elements M13, M23, and M33.
         * 
         * @param forwardVector 
         */
        void SetForward(const Vector3f& forwardVector) noexcept;

        /**
         * @brief Sets the translation factors of this Matrix4f used for homogeneous transformation, i.e., elements M14, M24, and M34.
         * 
         * @param translationX The translation X value.
         * @param translationY The translation Y value.
         * @param translationZ The translation Z value.
         */
        void SetTranslation(const float translationX, const float translationY, const float translationZ) noexcept;

        /**
         * @brief Sets the translation factors of this Matrix4f used for homogeneous transformation, i.e., elements M14, M24, and M34.
         * 
         * @param translation The Vector3f encoding the X, Y, and Z translation values.
         */
        void SetTranslation(const Vector3f& translation) noexcept;

        /**
         * @brief Sets the scale factors of this Matrix4f to a single value, i.e., elements M11, M22, and M33.
         * 
         * @param scale The degree to which this Matrix4f will scale a Vector3f along the X, Y, and Z axes.
         */
        void SetScale(const float scale) noexcept;

        /**
         * @brief Sets the scale factors of this Matrix4f, i.e., elements M11, M22, and M33.
         * 
         * @param scaleX The x-axis scale factor.
         * @param scaleY The y-axis scale factor.
         * @param scaleZ The z-axis scale factor.
         */
        void SetScale(const float scaleX, const float scaleY, const float scaleZ) noexcept;

        /**
         * @brief Gets the three-dimensional basis vector i-hat, i.e., elements M11, M21, and M31.
         * 
         * @return The i-hat basis vector as a Vector3f.
         */
        Vector3f GetRight() const noexcept;

        /**
         * @brief Gets the three-dimensional basis vector j-hat, i.e., elements M12, M22, and M32.
         * 
         * @return The j-hat basis vector as a Vector3f.
         */
        Vector3f GetUp() const noexcept;

        /**
         * @brief Gets the three-dimensional basis vector k-hat, i.e., elements M13, M23, and M33.
         * 
         * @return The k-hat basis vector as a Vector3f.
         */
        Vector3f GetForward() const noexcept;

        /**
         * @brief Gets the vector by which this Matrix4f translates Vector3f instances, i.e., elements M14, M24, and M34.
         * 
         * @return A Vector3f comprising the translation factors of this Matrix4f.
         */
        Vector3f GetTranslation() const noexcept;

        /**
         * @brief Gets the degrees to which this Matrix4f scales Vector3f instances along all axes, i.e., elements M11, M22, and M33.
         * 
         * @return A Vector3f comprising the scaling factors of this Matrix4f.
         */
        Vector3f GetScale() const noexcept;

        /**
         * @brief Creates a billboard transformation matrix capable of re-orienting any object such that it faces the camera. This Matrix4f operates in world coordinates.
         * 
         * @param objectPos The Vector3f position of the point that the Model will rotate around, in world coordinates.
         * @param cameraPos The Vector3f position of the Camera towards which the Model will be rotated, in world coordinates.
         * @param upVector The unit up-vector of the Camera.
         * @param forwardVector The unit forward-vector of the Camera.
         * @return The billboard matrix.
         */
        static Matrix4f CreateBillboard(Vector3f& objectPos, Vector3f& cameraPos, Vector3f& upVector, Vector3f& forwardVector) noexcept;

        /**
         * @brief Creates a cylindrical billboard transformation matrix with a constrained axis. This Matrix4f is capable of re-orienting any object, around
         * a single axis, such that it faces the Camera.
         * 
         * @param objectPos The Vector3f position of the point that the Model will rotate around, in world coordinates.
         * @param cameraPos The Vector3f position of the Camera towards which the Model will be rotated, in world coordinates.
         * @param upVector The unit up-vector of the Camera.
         * @param forwardVector The unit forward-vector of the Camera.
         * @param rotationAxis The axis around which the Model may rotate.
         * @return The constrained billboard matrix.
         */
        static Matrix4f CreateConstrainedBillboard(Vector3f& objectPos, Vector3f& cameraPos, Vector3f& upVector, Vector3f& forwardVector, Vector3f& rotationAxis) noexcept;

        /**
         * @brief Create a view matrix, capable of translating from world coordinates to camera coordinates, i.e., rotating and translating all world objects such
         * that the Camera is at the origin.
         * 
         * @param cameraPos The position of the Camera in world coordinates.
         * @param targetPos The position of the Model to transform in world coordinates.
         * @param upVector The up-vector of the Camera.
         * @return The view matrix.
         */
        static Matrix4f CreateLookAt(Vector3f& cameraPos, Vector3f& targetPos, Vector3f& upVector) noexcept;

        /**
         * @brief Creates an orthographic projection matrix, capable of projecting three-dimensional coordinates (e.g., a 3D scene) onto a two-dimensional plane
         * (e.g., a 2D screen), while maintaining parallel lines and causing the illusion that all objects are the same size, regardless of their distance from the Camera.
         * 
         * @param width The width of the view volume.
         * @param height The height of the view volume.
         * @param zNearPlane The minimum Z-value of the view volume.
         * @param zFarPlane The maximum Z-value of the view volume.
         * @return The orthographic projection matrix.
         */
        static Matrix4f CreateOrthographic(const float width, const float height, const float zNearPlane, const float zFarPlane) noexcept;

        /**
         * @brief Creates a customised orthographic projection matrix, capable of projecting three-dimensional coordinates (e.g., a 3D scene) onto a two-dimensional plane
         * (e.g., a 2D screen), while maintaining parallel lines and causing the illusion that all objects are the same size, regardless of their distance from the Camera.
         * 
         * @param left The minimum X-value of the view volume.
         * @param right The maximum X-value of the view volume.
         * @param bottom The minimum Y-value of the view volume.
         * @param top The maximum Y-value of the view volume.
         * @param zNearPlane The minimum Z-value of the view volume.
         * @param zFarPlane The maximum Z-value of the view volume.
         * @return The orthographic projection matrix.
         */
        static Matrix4f CreateOrthographicOffCentre(const float left, const float right, const float bottom, const float top, const float zNearPlane, const float zFarPlane) noexcept;

        /**
         * @brief Creates a perspective projection matrix, capable of projecting three-dimensional coordinates (e.g., a 3D scene) onto a two-dimensional plane
         * (e.g., a 2D screen), such that more distant objects appear smaller.
         * 
         * @param width The width of the view volume.
         * @param height The height of the view volume.
         * @param nearPlaneDistance The distance to the near view plane.
         * @param farPlaneDistance The distance to the far view plane.
         * @return The perspective projection matrix.
         */
        static Matrix4f CreatePerspective(const float width, const float height, const float nearPlaneDistance, const float farPlaneDistance) noexcept;

        /**
         * @brief Creates a perspective projection matrix from the provided FOV and aspect ratio, capable of projecting three-dimensional coordinates (e.g., a 3D scene) 
         * onto a two-dimensional plane (e.g., a 2D screen), such that more distant objects appear smaller.
         * 
         * @param fieldOfView The field of view in the y-direction, in radians.
         * @param aspectRatio The view space width divided by the height.
         * @param nearPlaneDistance The distance to the near view plane.
         * @param farPlaneDistance The distance to the far view plane.
         * @return The perspective projection matrix.
         */
        static Matrix4f CreatePerspectiveFOV(const float fieldOfView, const float aspectRatio, const float nearPlaneDistance, const float farPlaneDistance) noexcept;

        /**
         * @brief Creates a customised perspective projection matrix, capable of projecting three-dimensional coordinates (e.g., a 3D scene) 
         * onto a two-dimensional plane (e.g., a 2D screen), such that more distant objects appear smaller.
         * 
         * @param left The minimum X-value of the view volume.
         * @param right The maximum X-value of the view volume.
         * @param bottom The minimum Y-value of the view volume.
         * @param top The maximum Y-value of the view volume.
         * @param nearPlaneDistance The minimum Z-value of the view volume.
         * @param farPlaneDistance The maximum Z-value of the view volume.
         * @return The perspective projection matrix.
         */
        static Matrix4f CreatePerspectiveOffCentre(const float left, const float right, const float bottom, const float top, const float nearPlaneDistance, const float farPlaneDistance) noexcept;
        
        /**
         * @brief Creates the world matrix, a Matrix4f capable of transforming coordinates in Model-space to world space.
         * 
         * @param objectPos The position of the origin of the object in world coordinates.
         * @param upVector The up-vector of the object.
         * @param forwardVector The forward-vector of the object.
         * @return The world matrix.
         */
        static Matrix4f CreateWorld(const Vector3f& objectPos, const Vector3f& upVector, const Vector3f& forwardVector) noexcept;
        //static Matrix4f CreateReflection(Plane) noexcept;
        //static Matrix4f CreateShadow(Plane, Vector3 lightSource) noexcept

        /**
         * @brief Creates a rotation matrix about the x-axis by the provided angle in radians.
         * 
         * @param angle The angle in radians that this Matrix4f will rotate objects by.
         * @return A rotation matrix about the x-axis.
         */
        static Matrix4f CreateRotationX(const float angle) noexcept;

        /**
         * @brief Creates a rotation matrix about the x-axis at the position provided by the provided angle in radians.
         * 
         * @param angle The angle in radians that this Matrix4f will rotate objects by.
         * @param position The point about which this Matrix4f will rotate objects.
         * @return A rotation matrix about the x-axis.
         */
        static Matrix4f CreateRotationX(const float angle, const Vector3f& position) noexcept;

        /**
         * @brief Creates a rotation matrix about the y-axis by the provided angle in radians.
         * 
         * @param angle The angle in radians that this Matrix4f will rotate objects by.
         * @return A rotation matrix about the y-axis.
         */
        static Matrix4f CreateRotationY(const float angle) noexcept;

        /**
         * @brief Creates a rotation matrix about the y-axis at the position provided by the provided angle in radians.
         * 
         * @param angle The angle in radians that this Matrix4f will rotate objects by.
         * @param position The point about which this Matrix4f will rotate objects.
         * @return A rotation matrix about the y-axis.
         */
        static Matrix4f CreateRotationY(const float angle, const Vector3f& position) noexcept;

        /**
         * @brief Creates a rotation matrix about the z-axis by the provided angle in radians.
         * 
         * @param angle The angle in radians that this Matrix4f will rotate objects by.
         * @return A rotation matrix about the z-axis.
         */
        static Matrix4f CreateRotationZ(const float angle) noexcept;

        /**
         * @brief Creates a rotation matrix about the z-axis at the position provided by the provided angle in radians.
         * 
         * @param angle The angle in radians that this Matrix4f will rotate objects by.
         * @param position The point about which this Matrix4f will rotate objects.
         * @return A rotation matrix about the z-axis.
         */
        static Matrix4f CreateRotationZ(const float angle, const Vector3f& position) noexcept;

        /**
         * @brief Creates a scale matrix that uniformly scales Vector3f instances across all three dimensions.
         * 
         * @param scale The degree to which this Matrix4f will scale the x-, y-, and z-axes.
         * @return A scale matrix.
         */
        static Matrix4f CreateScale(const float scale) noexcept;

        /**
         * @brief Creates a scale matrix that scales Vector3f instances by the provided factors.
         * 
         * @param scaleX The x-axis scale factor.
         * @param scaleY The y-axis scale factor.
         * @param scaleZ The z-axis scale factor.
         * @return A scale matrix.
         */
        static Matrix4f CreateScale(const float scaleX, const float scaleY, const float scaleZ) noexcept;

        /**
         * @brief Creates a translation matrix that translates Vector3f instances by the provided factors.
         * 
         * @param translationX The x-axis translation factor.
         * @param translationY The y-axis translation factor.
         * @param translationZ The z-axis translation factor.
         * @return A translation matrix.
         */
        static Matrix4f CreateTranslation(const float translationX, const float translationY, const float translationZ) noexcept;

        /**
         * @brief Creates a translation matrix that translates Vector3f instances by the provided factors, encoded in a Vector3f.
         * 
         * @param translation The Vector3f encoding the x-, y-, and z-axis translation factors.
         * @return A translation matrix.
         */
        static Matrix4f CreateTranslation(const Vector3f& translation) noexcept;

        /**
         * @brief Linearly interpolates between two Matrix4f instances.
         * 
         * @param firstMatrix The first Matrix4f to interpolate from.
         * @param secondMatrix The second Matrix4f to interpolate from.
         * @param t The percentage between the first and second Matrix4f instances to interpolate at.
         * @return A linearly interpolated Matrix4f.
         */
        static Matrix4f Lerp(const Matrix4f& firstMatrix, const Matrix4f& secondMatrix, const float t) noexcept;

        /**
         * @brief Expresses this Matrix4f as an std::vector<float> in row major.
         * 
         * @return An std::vector<float> containing the elements of this Matrix4f.
         */
        const std::vector<float> ToArray() const noexcept override;

        /**
         * @brief Expresses this Matrix4f as an std::string with newlines.
         * 
         * @return An std::string displaying the elements of this Matrix4f.
         */
        std::string ToString() const noexcept;

        /**
         * @brief Expresses this Matrix4f as an std::string on a single line.
         * 
         * @return An std::string displaying the elements of this Matrix4f.
         */
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
FaceEngine::Vector3f operator *(const FaceEngine::Matrix4f& matrix, const FaceEngine::Vector3f& vector) noexcept;
FaceEngine::Vector4f operator *(const FaceEngine::Matrix4f& matrix, const FaceEngine::Vector4f& vector) noexcept;
FaceEngine::Matrix4f operator *(const FaceEngine::Matrix4f& matrix, const float scalar) noexcept;
FaceEngine::Matrix4f operator /(const FaceEngine::Matrix4f& matrix, const float scalar);
bool operator ==(const FaceEngine::Matrix4f& firstMatrix, const FaceEngine::Matrix4f& secondMatrix) noexcept;
bool operator !=(const FaceEngine::Matrix4f& firstMatrix, const FaceEngine::Matrix4f& secondMatrix) noexcept;

std::ostream& operator <<(std::ostream& cout, const FaceEngine::Matrix4f& matrix) noexcept;

#endif