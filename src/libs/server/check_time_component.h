#pragma once
#include "common.h"

class CheckTimeComponent
{
public:
    void CheckBegin();
    void CheckPoint(std::string key);

protected:
    uint64_t _beginTick;

    std::map<std::string, uint64_t> _aveTime;  // 平均时间
    std::map<std::string, uint64_t> _maxTicks;
};

