#ifndef FACEENGINE_MATH_MATRIX_H_
#define FACEENGINE_MATH_MATRIX_H_

#include <cstdint>
#include <type_traits>
#include <iostream>

#include "FaceEngine/Exception.h"

namespace FaceEngine
{
    template<typename T, const std::size_t R, const std::size_t C>
    class Matrix
    {
    static_assert(std::is_same<T, float>() || std::is_same<T, double>(), "Matrix must be of float or double.");
    static_assert(R > 0, "Rows must be more than zero.");
    static_assert(C > 0, "Columns must be more than zero.");

    private:
        std::size_t rows, columns;
        T** data;
    public:
        inline Matrix() noexcept
        {
            rows = R;
            columns = C;
            data = new T*[rows];

            for (std::size_t r = 0; r < rows; ++r)
            {
                data[r] = new T[columns];

                for (std::size_t c = 0; c < columns; ++c)
                {
                    data[r][c] = (T)0;
                }
            }
        }

        inline ~Matrix() noexcept
        {
            for (std::size_t r = 0; r < rows; ++r)
            {
                delete[] data[r];
            }

            delete[] data;
        }

        inline const std::size_t Rows() const noexcept
        {
            return rows;
        }

        inline const std::size_t Columns() const noexcept
        {
            return columns;
        }

        inline Matrix<T, R, C>& Identity() noexcept
        {
            if (rows == columns)
            {
                for (std::size_t r = 0; r < rows; ++r)
                {
                    for (std::size_t c = 0; c < columns; ++c)
                    {
                        if (r == c)
                        {
                            data[r][c] = (T)1;
                        }
                        else
                        {
                            data[r][c] = (T)0;
                        }
                    }
                }
            }

            return *this;
        }

        Matrix<float, 4, 4>& Ortho() noexcept;

        inline T* operator[](const std::size_t r) const
        {
            return &data[r][0];
        }
    };

    template<>
    inline Matrix<float, 4, 4>& Matrix<float, 4, 4>::Identity() noexcept
    {
        data[0][0] = 1.0f;
        data[0][1] = 0.0f;
        data[0][2] = 0.0f;
        data[0][3] = 0.0f;
        data[1][0] = 0.0f;
        data[1][1] = 1.0f;
        data[1][2] = 0.0f;
        data[1][3] = 0.0f;
        data[2][0] = 0.0f;
        data[2][1] = 0.0f;
        data[2][2] = 1.0f;
        data[2][3] = 0.0f;
        data[3][0] = 0.0f;
        data[3][1] = 0.0f;
        data[3][2] = 0.0f;
        data[3][3] = 1.0f;
        return *this;
    }

    std::ostream& operator<<(std::ostream&, const Matrix<float, 3, 3>&);
    std::ostream& operator<<(std::ostream&, const Matrix<float, 4, 4>&);

    using Matrix2f = Matrix<float, 2, 2>;
    using Matrix2x2f = Matrix<float, 2, 2>;
    using Matrix3f = Matrix<float, 3, 3>;
    using Matrix3x3f = Matrix<float, 3, 3>;
    using Matrix4f = Matrix<float, 4, 4>;
    using Matrix4x4f = Matrix<float, 4, 4>;
}

#endif