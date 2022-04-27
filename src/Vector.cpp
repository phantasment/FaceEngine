#include "FaceEngine/Math/Vector.h"

namespace FaceEngine
{
    std::ostream& operator<<(std::ostream& os, const Vector<float, 3>& vec)
    {
        os << "Vector3f[";

        for (std::size_t i = 0; i < 3; ++i)
        {
            os << vec[i];

            if (i != 2)
            {
                os << ", ";
            }
        }

        os << "]";
        return os;
    }

    std::ostream& operator<<(std::ostream& os, const Vector<float, 4>& vec)
    {
        os << "Vector4f[";

        for (std::size_t i = 0; i < 4; ++i)
        {
            os << vec[i];

            if (i != 3)
            {
                os << ", ";
            }
        }

        os << "]";
        return os;
    }
}