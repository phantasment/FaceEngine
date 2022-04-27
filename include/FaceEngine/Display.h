#ifndef FACEENGINE_DISPLAY_H_
#define FACEENGINE_DISPLAY_H_

#include <vector>

#include "FaceEngine/Resolution.h"

namespace FaceEngine
{
    class Display
    {
        friend class GraphicsDevice;
    private:
        std::vector<Resolution> resolutions;
        bool primary;
    public:
        inline const std::vector<Resolution>& Resolutions() const noexcept
        {
            return resolutions;
        }
        
        inline const bool IsPrimary() const noexcept
        {
            return primary;
        }

        inline const Resolution& MinResolution() const noexcept
        {
            return resolutions[0];
        }

        inline const Resolution& MaxResolution() const noexcept
        {
            return resolutions[resolutions.size() - 1];
        }
    };
}

#endif