#ifndef FACEENGINE_MATH_VECTOR_H_
#define FACEENGINE_MATH_VECTOR_H_

#include <cstdint>
#include <type_traits>
#include <iostream>

#include "FaceEngine/Exception.h"

namespace FaceEngine
{
    template<typename T, const std::size_t L>
    class Vector
    {
    static_assert(std::is_same<T, float>() || std::is_same<T, double>(), "Vector must be of float or double.");
    static_assert(L > 0, "Length must be more than zero.");

    private:
        std::size_t length;
        T* data;
    public:
        inline Vector() noexcept
        {
            length = L;
            data = new T[length];

            for (std::size_t i = 0; i < length; ++i)
            {
                data[i] = (T)0;
            }
        }

        inline ~Vector() noexcept
        {
            delete[] data;
        }

        inline const std::size_t Length() const noexcept
        {
            return length;
        }

        inline T& operator[](const std::size_t i) const
        {
            if (i >= length)
            {
                throw FaceEngine::Exception("index cannot be larger than length");
            }

            return data[i];
        }
    };

    std::ostream& operator<<(std::ostream&, const Vector<float, 3>&);
    std::ostream& operator<<(std::ostream&, const Vector<float, 4>&);

    using Vector2f = Vector<float, 2>;
    using Vector3f = Vector<float, 3>;
    using Vector4f = Vector<float, 4>;
}

#endif