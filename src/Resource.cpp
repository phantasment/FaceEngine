#include "FaceEngine/Resource.h"

namespace FaceEngine
{
    const bool Resource::IsDisposed() noexcept { return false; }

    void Resource::Dispose() noexcept { }
}