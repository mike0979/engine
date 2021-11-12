#pragma once
#include "server/system.h"
#include "server/entity.h"

class WorldProxyComponentGather :public Entity<WorldProxyComponentGather>, public IAwakeFromPoolSystem<>
{
public:
    void Awake() override;
    void BackToPool() override;

private:
    void SyncWorldInfoToGather();

private:
    uint64_t _worldSn{ 0 };
    int _worldId{ 0 };
};

