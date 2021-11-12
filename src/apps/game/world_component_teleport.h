#pragma once
#include "server/component.h"
#include "server/system.h"

class WorldProxy;
class Player;
class ResourceWorld;
class TeleportObject;

class WorldComponentTeleport :public Component<WorldComponentTeleport>, public IAwakeFromPoolSystem<>
{
public:
	void Awake() override;
    void BackToPool() override;

    bool IsTeleporting(Player* pPlayer);

	void CreateTeleportObject(int worldId, Player* pPlayer);
	void HandleBroadcastCreateWorldProxy(int worldId, uint64_t worldSn);
	void BroadcastSyncPlayer(uint64_t playerSn);

protected:
    void CreateWorldFlag(WorldProxy* pWorldProxy, int targetWorldId, TeleportObject* pObj);
    void CreateSyncFlag(WorldProxy* pWorldProxy, TeleportObject* pObj);

	bool Check(TeleportObject* pObj);

private:
    // <playersn, obj>
	std::map<uint64_t, TeleportObject*> _objects;
};

