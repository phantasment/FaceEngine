#ifndef FACEENGINE_RESOURCEMANAGER_H_
#define FACEENGINE_RESOURCEMANAGER_H_

#include <vector>
#include <cstdint>

#include "FaceEngine/Resource.h"

namespace FaceEngine
{
    class ResourceManager
    {
    private:
        std::vector<Resource*> resources;
        std::vector<Resource*> marked;
    public:
        inline ResourceManager() { }

        void AddResource(Resource*);
        void MarkResource(Resource*);
        void DisposeResource(Resource*);
        void DisposeAllResources();
        void HandleMarked();
    };
}

#endif