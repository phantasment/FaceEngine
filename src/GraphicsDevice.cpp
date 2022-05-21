#include "FaceEngine/GraphicsDevice.h"

namespace FaceEngine
{
    GraphicsDevice::GraphicsDevice()
    {
        int monitorCount;
        int vidmodeCount;
        GLFWmonitor** monitors = glfwGetMonitors(&monitorCount);

        for (int i = 0; i < monitorCount; ++i)
        {
            const GLFWvidmode* vidmodes = glfwGetVideoModes(monitors[i], &vidmodeCount);
            Display display;
            display.handle = monitors[i];
            display.primary = i == 0;

            for (int j = 0; j < vidmodeCount; ++j)
            {
                if (vidmodes[j].width >= 800 || vidmodes[j].height >= 600)
                {
                    display.resolutions.emplace_back(vidmodes[j].width, vidmodes[j].height);
                }
            }

            displays.push_back(std::move(display));
        }
    }
}