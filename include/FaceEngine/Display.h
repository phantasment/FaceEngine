#ifndef FACEENGINE_DISPLAY_H_
#define FACEENGINE_DISPLAY_H_

#include <vector>

#include "FaceEngine/Resolution.h"
#include "FaceEngine/OGL.h"

namespace FaceEngine
{
    class Display
    {
        friend class GraphicsDevice;
    private:
        GLFWmonitor* handle;
        std::vector<Resolution> resolutions;
        bool primary;
    public:
        inline GLFWmonitor* GetHandle() const noexcept { return handle; }
        inline const std::vector<Resolution>& GetResolutions() const noexcept { return resolutions; }
        inline const bool IsPrimary() const noexcept { return primary; }
        inline const Resolution& GetMinResolution() const noexcept { return resolutions[0]; }
        inline const Resolution& GetMaxResolution() const noexcept { return resolutions[resolutions.size() - 1]; }
    };
}

#endif