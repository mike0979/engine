#pragma once
#include "system.h"
#include "entity.h"

class Packet;

class SocketLocator :public Entity<SocketLocator>, public IAwakeSystem<>
{
public:
    void Awake() override;
    void BackToPool() override;

    void RegisterToLocator(int socket, uint64_t sn);
    void Remove(int socket);
    uint64_t GetTargetEntitySn(int socket);

private:
    void HandleNetworkDisconnect(Packet* pPacket);

private:
    std::mutex _lock;
    std::map<int, uint64_t> _componentes;
};

