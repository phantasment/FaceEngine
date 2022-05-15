#include "FaceEngine/Resource.h"

namespace FaceEngine
{
    const bool Resource::IsDisposed() noexcept { return true; }

    void Resource::Dispose() noexcept { }
}