#include "FaceEngine/ResourceManager.h"

namespace FaceEngine
{
    bool ResourceManager::TrackResource(Resource* r)
    {
        return resources.insert(r).second;
    }

    bool ResourceManager::UntrackResource(Resource* r)
    {
        return resources.erase(r);
    }

    bool ResourceManager::DisposeResource(Resource* r)
    {
        if (disposingAll)
        {
            return true;
        }
        else if (resources.erase(r))
        {
            r->Dispose();
            delete r;
            return true;
        }
        else
        {
            return false;
        }
    }

    void ResourceManager::DisposeAllResources()
    {
        disposingAll = true;

        while (!resources.empty())
        {
            Resource* r = (*resources.begin());
            r->Dispose();
            delete r;
            resources.erase(r);
        }

        resources.clear();
        disposingAll = false;
    }
}