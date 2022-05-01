/**
 * @file Vector2f.h
 * @author Ryan Duncan (ryanduncan@phantasm.com)
 * @brief Contains the Vector2f class.
 * @version 0.1
 * @date 2022-04-27
 * 
 * @copyright Copyright (c) 2022
 */

#ifndef FACEENGINE_MATH_VECTOR2F_H_
#define FACEENGINE_MATH_VECTOR2F_H_

#include "FaceEngine/Math/Vector.h"
#include "FaceEngine/Math/Matrix3f.h"
#include <iostream>

namespace FaceEngine
{
    /**
     * @brief A 2D floating-point vector.
     */
    class Vector2f : public Vector
    {
    public:
        /**
         * @brief The x-coordinate of this Vector2f.
         */
        float X;

        /**
         * @brief The y-coordinate of this Vector2f.
         */
        float Y;

        /**
         * @brief A Vector2f with both components set to zero.
         */
        static const Vector2f Zero;
        
        /**
         * @brief A Vector2f with both components set to one.
         */
        static const Vector2f One;

        /**
         * @brief A Vector2f of length one, pointed towards the positive x-axis.
         */
        static const Vector2f UnitX;

        /**
         * @brief A Vector2f of length one, pointed towards the positive y-axis.
         */
        static const Vector2f UnitY;

        /**
         * @brief Constructs a new Vector2f object with both components set to zero.
         */
        Vector2f() noexcept;

        /**
         * @brief Constructs a new Vector2f object with both components set to value provided.
         * 
         * @param value The value of both X and Y.
         */
        Vector2f(float value) noexcept;

        /**
         * @brief Constructs a new Vector2f object with specified X and Y values.
         * 
         * @param x The value of the X component.
         * @param y The value of the Y component.
         */
        Vector2f(float x, float y) noexcept;

        /**
         * @brief Calculates the dot product between this Vector2f and the provided Vector2f.
         * 
         * @param vector The Vector2f to dot with.
         * @return The dot product as a float.
         */
        float Dot(const Vector2f& vector) const noexcept;

        /**
         * @brief Calculates the magnitude, or length, of this Vector2f.
         * 
         * @return The magnitude of this Vector2f as a float.
         */
        float GetMagnitude() const noexcept;

        /**
         * @brief Calculates the distance between the tip of this Vector2f and that of the provided Vector2f.
         * 
         * @param vector The Vector2f to calculate the distance from.
         * @return The distance between the tips of these two Vector2f objects, as a float.
         */
        float Distance(const Vector2f& vector) const noexcept;

        /**
         * @brief Translates this Vector2f into a readable string.
         * 
         * @return An std::string with information regarding this Vector2f.
         */
        std::string ToString() const noexcept;

        /**
         * @brief Adds the provided Vector2f to this instance, component-wise.
         * 
         * @param vector The Vector2f to add to this instance.
         */
        void Add(const Vector2f& vector) noexcept;

        /**
         * @brief Subtracts the provided Vector2f from this instance, component-wise.
         * 
         * @param vector The Vector2f to subtract from this instance.
         */
        void Subtract(const Vector2f& vector) noexcept;

        /**
         * @brief Multiplies each component of this Vector2f by the provided scalar.
         * 
         * @param scalar The scalar to multiply by.
         */
        void Multiply(const float scalar) noexcept;

        /**
         * @brief Multiplies this Vector2f with the provided Vector2f component-wise.
         * 
         * @param vector The Vector2f to multiply by.
         */
        void Multiply(const Vector2f& vector) noexcept;

        /**
         * @brief Divides this Vector2f instance by the provided scalar.
         * 
         * @throws FaceEngine::Exception - thrown when scalar is zero.
         * @param scalar The scalar to divide by.
         */
        void Divide(const float scalar);

        /**
         * @brief Transforms this Vector2f with the provided Matrix3f (via homogenenous transformation).
         * 
         * @param matrix The Matrix3f to multiply this Vector2f by.
         */
        void Transform(const Matrix3f& matrix) noexcept;

        /**
         * @brief Checks if the components of this Vector2f are equal to the components of the provided Vector2f.
         * 
         * @param vector The Vector2f to compare.
         * @return A boolean value describing whether these two Vector2f instances are equal.
         */
        bool Equals(const Vector2f& vector) const noexcept;

        /**
         * @brief Flips the direction of this Vector2f.
         */
        void Negate() noexcept;

        /**
         * @brief Runs a floor function on both components of this Vector2f.
         */
        void Floor() noexcept;

        /**
         * @brief Runs a ceiling function on both components of this Vector2f.
         */
        void Ceiling() noexcept;

        /**
         * @brief Rounds both components of this Vector2f.
         */
        void Round() noexcept;

        /**
         * @brief Clamps the X and Y components of this Vector2f to between the X and Y components of the parameter Vector2f instances, respectively.
         * 
         * @param firstBound The first boundary Vector2f.
         * @param secondBound The second boundary Vector2f.
         */
        void Clamp(const Vector2f& firstBound, const Vector2f& secondBound) noexcept;

        /**
         * @brief Normalises this Vector2f, or reduces its length to one while maintaining its direction.
         */
        void Normalise() noexcept;

        /**
         * @brief Adds the right-hand Vector2f to the left-hand one.
         * 
         * @param vector The Vector2f to add.
         */
        void operator +=(const Vector2f& vector) noexcept;

        /**
         * @brief Subtracts the right-hand Vector2f from the left-hand one.
         * 
         * @param vector The Vector2f to subtract.
         */
        void operator -=(const Vector2f& vector) noexcept;

        /**
         * @brief Multiplies the left-hand Vector2f by the right-hand scalar.
         * 
         * @param scalar The scalar to multiply by.
         */
        void operator *=(const float scalar) noexcept;

        /**
         * @brief Multiplies the left-hand Vector2f by the right-hand Vector2f component-wise.
         * 
         * @param vector The Vector2f to multiply by.
         */
        void operator *=(const Vector2f& vector) noexcept;

        /**
         * @brief Transforms the left-hand Vector2f by multiplying it by the right-hand Matrix3f homogeneneously.
         * 
         * @param matrix The matrix to multiply by.
         */
        void operator *=(const Matrix3f& matrix) noexcept;

        /**
         * @brief Divides the left-hand Vector2f by the right-hand scalar.
         * 
         * @throws FaceEngine::Exception - thrown when scalar is zero.
         * @param scalar The scalar to divide by.
         */
        void operator /=(const float scalar);

        /**
         * @brief Negates this Vector2f.
         * 
         * @return A Vector2f in the opposite direction of the original.
         */
        Vector2f operator -() const noexcept;

        /**
         * @brief Gets the component at the provided index.
         * 
         * @throws FaceEngine::Exception - when the index is not 0 or 1 (out of bounds).
         * @param index The index of the component to retrieve.
         * @return The component at the specified index.
         */
        float operator [](int index) const;

        /**
         * @brief Gets the component at the provided index.
         * 
         * @throws FaceEngine::Exception - when the index is not 0 or 1 (out of bounds).
         * @param index The index of the component to retrieve.
         * @return The component at the specified index.
         */
        float& operator [](int index);

        /**
         * @brief Factory method that calculates a Vector2f with the largest components of the two provided Vector2f instances.
         * 
         * @param firstVector The first Vector2f bound.
         * @param secondVector The second Vector2f bound.
         * @return A Vector2f with maximised components.
         */
        static Vector2f Max(const Vector2f& firstVector, const Vector2f& secondVector) noexcept;

        /**
         * @brief Factory method that calculates a Vector2f with the smallest components of the two provided Vector2f instances.
         * 
         * @param firstVector The first Vector2f bound.
         * @param secondVector The second Vector2f bound.
         * @return A Vector2f with minimised components.
         */
        static Vector2f Min(const Vector2f& firstVector, const Vector2f& secondVector) noexcept;

        /**
         * @brief Factory method that linearly interpolates between two provided Vector2f instances.
         * 
         * @param firstVector The first Vector2f to interpolate between.
         * @param secondVector The second Vector2f to interpolate between.
         * @param t The percentage between the first and second Vector2f instances to interpolate at.
         * @return A linearly interpolated Vector2f.
         */
        static Vector2f Lerp(const Vector2f& firstVector, const Vector2f& secondVector, const float t) noexcept;

        /**
         * @brief Expresses the X and Y components of this Vector2f as an std::vector<float>.
         * 
         * @return An std::vector<float> containing the X and Y components of this Vector2f.
         */
        const std::vector<float> ToArray() const noexcept override;
    };
}

/**
 * @brief Adds the left- and right-hand Vector2f instances together component-wise.
 * 
 * @param firstVector The first Vector2f to add.
 * @param secondVector The second Vector2f to add.
 * @return The sum of the two Vector2f instances. 
 */
FaceEngine::Vector2f operator +(const FaceEngine::Vector2f& firstVector, const FaceEngine::Vector2f& secondVector) noexcept;

/**
 * @brief Subtracts the right-hand Vector2f from the left-hand one.
 * 
 * @param firstVector The Vector2f to subtract from.
 * @param secondVector The Vector2f to subtract.
 * @return The difference of the two Vector2f instances.
 */
FaceEngine::Vector2f operator -(const FaceEngine::Vector2f& firstVector, const FaceEngine::Vector2f& secondVector) noexcept;

/**
 * @brief Multiplies the Vector2f by the provided scalar.
 * 
 * @param vector The Vector2f to multiply.
 * @param scalar The scalar to multiply by.
 * @return The product of the Vector2f and the scalar.
 */
FaceEngine::Vector2f operator *(const FaceEngine::Vector2f& vector, const float scalar) noexcept;

/**
 * @brief Multiplies these Vector2f instances component-wise.
 * 
 * @param firstVector The first Vector2f to multiply.
 * @param secondVector The second Vector2f to multiply.
 * @return The component-wise product of these two Vector2f instances.
 */
FaceEngine::Vector2f operator *(const FaceEngine::Vector2f& firstVector, const FaceEngine::Vector2f& secondVector) noexcept;

/**
 * @brief Transforms the Vector2f by the provided Matrix3f via homogeneous multiplication.
 * 
 * @param vector The Vector2f to transform.
 * @param matrix The Matrix3f to multiply by.
 * @return A transformed Vector2f.
 */
FaceEngine::Vector2f operator *(const FaceEngine::Vector2f& vector, const FaceEngine::Matrix3f& matrix) noexcept;

/**
 * @brief Divides the Vector2f by the provided scalar.
 * 
 * @throws FaceEngine::Exception - thrown when scalar is zero.
 * @param vector The Vector2f to divide.
 * @param scalar The scalar to divide by.
 * @return The quotient of the Vector2f and the scalar.
 */
FaceEngine::Vector2f operator /(const FaceEngine::Vector2f& vector, const float scalar);

/**
 * @brief Compares the two provided Vector2f instances and checks if their components are equal.
 * 
 * @param firstVector The first Vector2f to compare.
 * @param secondVector The second Vector2f to compare.
 * @return A boolean describing whether the two Vector2f instances are equal.
 */
bool operator ==(const FaceEngine::Vector2f& firstVector, const FaceEngine::Vector2f& secondVector) noexcept;

/**
 * @brief Compares the two provided Vector2f instances and checks if their components are unequal.
 * 
 * @param firstVector The first Vector2f to compare.
 * @param secondVector The second Vector2f to compare.
 * @return A boolean describing whether the two Vector2f instances are unequal.
 */
bool operator !=(const FaceEngine::Vector2f& firstVector, const FaceEngine::Vector2f& secondVector) noexcept;

/**
 * @brief Inserts a string version of Vector2f into the provided stream.
 * 
 * @param os The stream to insert into.
 * @param vec2 The Vector2f to insert.
 * @return The updated stream.
 */
std::ostream& operator <<(std::ostream& os, const FaceEngine::Vector2f& vec2);

#endif