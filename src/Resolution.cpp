#include "FaceEngine/Resolution.h"

namespace FaceEngine
{
    std::ostream& operator<<(std::ostream& os, const FaceEngine::Resolution& r) noexcept
    {
        os << r.GetWidth() << "x" << r.GetHeight();
        return os;
    }
}