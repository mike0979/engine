#include "resource_help.h"
#include "server/thread_mgr.h"

ResourceManager* ResourceHelp::GetResourceManager()
{
    return ThreadMgr::GetInstance()->GetEntitySystem()->GetComponent<ResourceManager>();
}
