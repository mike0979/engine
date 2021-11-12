#pragma once
#include "server/entity.h"

#include "player/player.h"

class PlayerManagerComponent:public Entity<PlayerManagerComponent>, public IAwakeFromPoolSystem<>
{
public:
	void Awake() override;
    void BackToPool() override;

	Player* AddPlayer(uint64_t playerSn, uint64_t worldSn, NetIdentify* pNetIdentify);
	Player* GetPlayerBySn(uint64_t playerSn);
	void RemovePlayerBySn(uint64_t playerSn);
    void RemoveAllPlayers(NetIdentify* pNetIdentify);

	int OnlineSize() const;
	std::map<uint64_t, Player*>* GetAll();

private:
	std::map<uint64_t, Player*> _players;
};

