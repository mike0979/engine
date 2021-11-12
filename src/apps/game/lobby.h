#pragma once
#include "player/world_base.h"
#include "server/system.h"
#include "server/entity.h"
#include "server/socket_object.h"

class Packet;
class Player;

class Lobby : public Entity<Lobby>, public IWorld, public IAwakeSystem<>
{
public:
	void Awake() override;
	void BackToPool() override;


private:
    Player* GetPlayer(NetIdentify* pIdentify);

    void HandleNetworkDisconnect(Packet* pPacket);
    void HandleLoginByToken(Packet* pPacket);
    void HandleGameTokenToRedisRs(Packet* pPacket);
    void HandleQueryPlayerRs(Packet* pPacket);
    void HandleQueryWorldRs(Packet* pPacket);
    void HandleBroadcastCreateWorldProxy(Packet* pPacket);
    void HandleTeleportAfter(Player* pPlayer, Packet* pPacket);

    // 进入公共地图
    void EnterPublicWorld(Player* pPlayer);

private:
	std::map<int, std::set<uint64_t>> _waitingForWorld;
    std::map<uint64_t, std::set<uint64_t>> _waitingForDungeon;
};

