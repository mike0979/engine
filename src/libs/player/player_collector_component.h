#pragma once
#include "server/system.h"
#include "server/component.h"
#include "server/socket_object.h"

class Player;

class PlayerCollectorComponent :public Component<PlayerCollectorComponent>, public IAwakeFromPoolSystem<>
{
public:
	void Awake() override;
    void BackToPool() override;

	Player* AddPlayer(NetIdentify* pIdentify, std::string account);

	void RemovePlayerBySocket(int socket);
	void RemovePlayerBySn(uint64_t playerSn);
    void RemoveAllPlayerAndCloseConnect();

	Player* GetPlayerBySocket(int socket);
	Player* GetPlayerByAccount(std::string account);
	Player* GetPlayerBySn(uint64_t playerSn);

	int OnlineSize() const;
	std::map<int, Player*>& GetAll();

protected:
    void RemovePlayer(Player* pPlayer);

private:
	// <socket, Player*>
	std::map<int, Player*> _players;

	// <account, socket>
	std::map <std::string, int> _accounts;
};

