#pragma once
#include "component.h"
#include "system.h"
#include "common.h"

#include <map>
#include <set>

enum class TraceType
{
    Packet = 0,
    Connector = 1,
    Player = 2,
    Time = 3,
};

class TraceDetail
{
public:
    void Trace(const std::string& trace);
    void Show();

private:
    std::list<std::string> _details;
};

class TraceComponent :public Component<TraceComponent>, public IAwakeSystem<>
{
public:
    void Awake() override;
    void BackToPool() override;

    void TraceAccount(std::string account, int socket);
    void ShowAccount(const std::string& account);

    void Trace(TraceType iType, int key, const std::string& trace);
    void Show(TraceType iType, int key);

    void Clean();

private:
    std::mutex _lock;
    std::map <TraceType, std::map<int, TraceDetail>> _traces;

    // player??Ӧ??socket
    std::map<std::string, std::set<int>> _accounts;
};
