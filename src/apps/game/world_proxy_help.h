#pragma once
#include "server/common.h"

class Player;

class WorldProxyHelp
{
public:
	static void Teleport(Player* pPlayer, uint64_t lastWorldSn, uint64_t targetWorldSn);
};

