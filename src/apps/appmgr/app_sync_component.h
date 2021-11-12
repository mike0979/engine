#pragma once

#include "server/sync_component.h"
#include "server/system.h"
#include <json/writer.h>

class AppSyncComponent :public Entity<AppSyncComponent>, public SyncComponent, public IAwakeSystem<>
{
public:
    void Awake() override;
    void BackToPool() override;

protected:
    // 
    void HandleHttpRequestLogin(Packet* pPacket);
    void HandleAppInfoSync(Packet* pPacket);
    void HandleNetworkDisconnect(Packet* pPacket) override;

private:
    void SyncGameInfoToLogin();

private:
    Json::StreamWriter* _jsonWriter{ nullptr };
};

