#pragma once
#include "system.h"
#include "entity.h"
#include "util_time.h"

#include <map>

class Packet;

struct ThreadEfficiencyInfo
{
    ThreadType ThreadTypeKey;
    uint64_t UpdateTime;  // udpateƽ��ʱ��
    timeutil::Time LastRecvTime;
    uint64_t UpdateTimeMax;
};

class ConsoleEfficiencyComponent :public Entity<ConsoleEfficiencyComponent>, public IAwakeSystem<>
{
public:
    void Awake() override;
    void BackToPool() override;

private:
    void HandleCmdEfficiency(Packet* pPacket);
    void HandleEfficiency(Packet* pPacket);

private:
    // threa id, ThreadEfficiencyInfo
    std::map<std::string, ThreadEfficiencyInfo> _threads;
};

