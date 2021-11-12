#pragma once
#include "server/component.h"
#include "server/system.h"
#include "player/player_component.h"

class PlayerComponentDetail :public Component<PlayerComponentDetail>, public IAwakeFromPoolSystem<>, public PlayerComponent
{
public:
    void Awake() override;
    void BackToPool() override;

    void ParserFromProto(const Proto::Player& proto) override;
    void SerializeToProto(Proto::Player* pProto) override;

    Proto::Gender GetGender() const;

private:
    Proto::Gender _gender;
};

