#pragma once
#include "server/entity.h"

class Packet;

class WorldProxyLocator :public Entity<WorldProxyLocator>, public IAwakeSystem<>
{
public:
	void Awake() override;
    void BackToPool() override;

	void RegisterToLocator(int worldId, uint64_t worldSn);
	void Remove(int worldId, uint64_t worldSn);

	bool IsExistDungeon(uint64_t worldSn);
	uint64_t GetWorldSnById(int worldId);

private:
	void HandleBroadcastCreateWorld(Packet* pPacket);

private:
	std::mutex _lock;

	// <world id, world sn>
	std::map<int, uint64_t> _publics; // 公共地图

	// <world sn>
	std::set<uint64_t> _worlds;  // 副本只存sn
};

