#pragma once
#include "server/entity.h"
#include "server/system.h"

class Packet;

class WorldOperatorComponent : public Entity<WorldOperatorComponent>, public IAwakeSystem<>
{
public:
	void Awake() override;
    void BackToPool() override;

private:
	void HandleCreateWorld(Packet* pPacket);
};
