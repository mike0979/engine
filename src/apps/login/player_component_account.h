#pragma once
#include "server/component.h"
#include "server/system.h"

class PlayerComponentAccount :public Component<PlayerComponentAccount>, public IAwakeFromPoolSystem<std::string>
{
public:
    void Awake(std::string password) override;
    void BackToPool() override;

    std::string GetPassword() const;

    void SetSelectPlayerSn(uint64_t sn);
    uint64_t GetSelectPlayerSn() const;

    void SetLastGameId(int gameId);
    int GetLastGameId() const;

private:
    std::string _password;
    uint64_t _selectPlayerSn{ 0 };
    int _lastGameId{ 0 };
};

