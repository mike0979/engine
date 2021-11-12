#pragma once
#include "server/common.h"
#include "server/socket_object.h"
#include "server/entity.h"
#include "server/system.h"

class Player :public Entity<Player>, public NetIdentify,
    virtual public IAwakeFromPoolSystem<NetIdentify*, std::string>,
    virtual public IAwakeFromPoolSystem<NetIdentify*, uint64_t, uint64_t>
{
public:
    void Awake(NetIdentify* pIdentify, std::string account) override;
    void Awake(NetIdentify* pIdentify, uint64_t playerSn, uint64_t worldSn) override;
    void BackToPool() override;

    std::string GetAccount() const;
    std::string GetName() const;
    uint64_t GetPlayerSN() const;

    Proto::Player& GetPlayerProto();

    void ParseFromStream(uint64_t playerSn, std::stringstream* pOpStream);
    void ParserFromProto(uint64_t playerSn, const Proto::Player& proto);
    void SerializeToProto(Proto::Player* pProto) const;

protected:
    std::string _account{ "" };
    std::string _name{ "" };

    uint64_t _playerSn{ 0 };
    Proto::Player _player;
};

