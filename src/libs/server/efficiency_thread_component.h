#pragma once
#include "system.h"
#include "thread_type.h"
#include "entity.h"

#include <thread>

#define ThreadEfficiencyTime 5

class Packet;

class EfficiencyThreadComponent :public Entity<EfficiencyThreadComponent>, public IAwakeSystem<ThreadType, std::thread::id>
{
public:
    void Awake(ThreadType threadType, std::thread::id threadId) override;
    void BackToPool() override;

    void UpdateTime(uint64_t disTime);
    void Sync() const;

private:
    // test update ִ��ƽ��ʱ��
    uint64_t _efficiencyUpdateTime{ 0 };

    std::string _threadId{ "" };
    ThreadType _threadType{ ThreadType::MainThread };
};

