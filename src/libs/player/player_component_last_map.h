#pragma once
#include "server/component.h"

#include "player_component.h"
#include "server/vector3.h"
#include "server/system.h"

struct LastWorld
{
	int WorldId{ 0 };
	uint64_t WorldSn{ 0 };
	Vector3 Position{ 0, 0,0 };

	LastWorld(const int worldId, const uint64_t worldSn, const Vector3 pos);

	LastWorld(Proto::LastWorld proto);

	void SerializeToProto(Proto::LastWorld* pProto) const;
};

class PlayerComponentLastMap :public Component<PlayerComponentLastMap>, public IAwakeFromPoolSystem<>, public PlayerComponent
{
public:
	void Awake() override;
    void BackToPool() override;

	void ParserFromProto(const Proto::Player& proto) override;
	void SerializeToProto(Proto::Player* pProto) override;

	LastWorld* GetLastPublicMap() const;
	LastWorld* GetLastDungeon() const;
	LastWorld* GetCur() const;

	void EnterWorld(int worldId, uint64_t worldSn);
	void SetCurWorld(int worldId);

protected:
	void EnterDungeon(int worldId, uint64_t worldSn, Vector3 position);	

private:
	// 一个是公共地图的位置，一个是副本位置
	LastWorld* _pPublic{ nullptr };
	LastWorld* _pDungeon{ nullptr };

	int _curWorldId{ 0 };
};

