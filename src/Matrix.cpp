#include "FaceEngine/Math/Matrix.h"

namespace FaceEngine
{
    Matrix<float, 4, 4>& Matrix<float, 4, 4>::Ortho() noexcept
    {
        return *this;
    }

    std::ostream& operator<<(std::ostream& os, const Matrix<float, 3, 3>& mat)
    {
        os << "Matrix3f\n[";

        for (std::size_t r = 0; r < 3; ++r)
        {
            if (r != 0)
            {
                os << ' ';
            }
            
            for (std::size_t c = 0; c < 3; ++c)
            {
                os << mat[r][c];

                if (c != 2)
                {
                    os << ", ";
                }
            }

            if (r < 2)
            {
                os << '\n';
            }
            else
            {
                os << ']';
            }
        }
        
        return os;
    }

    std::ostream& operator<<(std::ostream& os, const Matrix<float, 4, 4>& mat)
    {
        os << "Matrix4f\n[";

        for (std::size_t r = 0; r < 4; ++r)
        {
            if (r != 0)
            {
                os << ' ';
            }
            
            for (std::size_t c = 0; c < 4; ++c)
            {
                os << mat[r][c];

                if (c != 3)
                {
                    os << ", ";
                }
            }

            if (r < 3)
            {
                os << '\n';
            }
            else
            {
                os << ']';
            }
        }

        return os;
    }
}