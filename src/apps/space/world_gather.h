#pragma once

#include "server/entity.h"
#include "server/system.h"

class Packet;

class WorldGather :public Entity<WorldGather>, public IAwakeFromPoolSystem<>
{
public:
	void Awake() override;
	void BackToPool() override;

private:
	void SyncSpaceInfo();
	void HandleWorldSyncToGather(Packet* pPacket);
	void HandleCmdWorld(Packet* pPacket);

private:
	// <map sn, map player count>
	std::map<uint64_t, int> _maps;
};
