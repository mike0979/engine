#pragma once
#include "server/system.h"
#include "server/util_time.h"
#include "server/component_collections.h"

class MoveSystem : public ISystem<MoveSystem>
{
public:
    MoveSystem();
    void Update(EntitySystem* pEntities) override;

private:
    timeutil::Time _lastTime;
    ComponentCollections* _pCollections{ nullptr };
};

