#pragma once

#include "server/system.h"
#include "server/entity.h"

class Packet;

struct WorldProxyInfo
{
	uint64_t WorldSn;
	int WorldId;
	int Online;
};

class WorldProxyGather :public Entity<WorldProxyGather>, public IAwakeSystem<>
{
public:
	void Awake() override;
    void BackToPool() override;

private:
	void SyncGameInfo();
	void HandleWorldProxySyncToGather(Packet* pPacket);
	void HandleCmdWorldProxy(Packet* pPacket);

private:
	std::map<uint64_t, WorldProxyInfo> _maps;
};
