#pragma once

#include "server/common.h"
#include "server/component.h"
#include "server/system.h"

#include <sstream>

// player 组件，处理PlayerList
class PlayerComponentProtoList :public Component<PlayerComponentProtoList>, public IAwakeFromPoolSystem<>
{
public:
    void Awake() override {}
    void BackToPool() override;

    void Parse(Proto::PlayerList& proto);
    std::stringstream* GetProto(uint64_t sn);

private:
    std::map<uint64_t, std::stringstream*> _protos;
};

