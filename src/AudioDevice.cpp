#include "FaceEngine/AudioDevice.h"

namespace FaceEngine
{
    AudioDevice::AudioDevice()
    {
        alDevice = alcOpenDevice(nullptr);

        if (!alDevice)
        {
            throw Exception::FromMessage("FaceEngine::AudioDevice::AudioDevice", "Couldn't create audio device.");
        }

        alContext = alcCreateContext(alDevice, nullptr);

        if (!alcMakeContextCurrent(alContext))
        {
            alcDestroyContext(alContext);
            alcCloseDevice(alDevice);
            throw Exception::FromMessage("FaceEngine::AudioDevice::AudioDevice", "Couldn't create audio device.");
        }
    }

    AudioDevice::~AudioDevice()
    {
        alcDestroyContext(alContext);
        alcCloseDevice(alDevice);
    }
}