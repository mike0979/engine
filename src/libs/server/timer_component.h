#pragma once
#include "util_time.h"
#include "system.h"
#include "entity.h"

#include <list>
#include <vector>

struct Timer
{
    // �´ε���ʱ��
    timeutil::Time NextTime;

    // ���ú���
    TimerHandleFunction Handler;

    // �״�ִ��ʱ�ӳ���
    int DelaySecond;

    // ���ʱ��(�룩
    int DurationSecond;

    // �ܵ��ô�����0Ϊ���ޣ�
    int CallCountTotal;

    // ��ǰ���ô��� 
    int CallCountCur;

    // ����ɾ������ʱ�ҵ�Timer
    uint64_t SN;
};

class TimerComponent :public Entity<TimerComponent>, public IAwakeSystem<>
{
public:
    void Awake() override;
    void BackToPool() override;

    uint64_t Add(int total, int durations, bool immediateDo, int immediateDoDelaySecond, TimerHandleFunction handler);
    void Remove(std::list<uint64_t>& timers);

    bool CheckTime();
    Timer PopTimeHeap();

    void Update();

protected:
    void Add(Timer& data);

private:
    std::vector<Timer> _heap;
};