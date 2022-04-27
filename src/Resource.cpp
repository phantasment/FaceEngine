#include "FaceEngine/Resource.h"

namespace FaceEngine
{
    const bool Resource::IsDisposed() const noexcept { return false; }

    void Resource::Dispose() const noexcept { }
}