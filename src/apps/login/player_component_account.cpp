#include "player_component_account.h"

void PlayerComponentAccount::Awake(const std::string password)
{
	_password = password;
	_selectPlayerSn = 0;
	_lastGameId = INVALID_ID;
}

void PlayerComponentAccount::BackToPool()
{
    _password = "";
    _selectPlayerSn = 0;
    _lastGameId = INVALID_ID;
}

std::string PlayerComponentAccount::GetPassword() const
{
	return _password;
}

void PlayerComponentAccount::SetSelectPlayerSn(const uint64_t sn)
{
	_selectPlayerSn = sn;
}

uint64_t PlayerComponentAccount::GetSelectPlayerSn() const
{
	return _selectPlayerSn;
}

void PlayerComponentAccount::SetLastGameId(int gameId)
{
	_lastGameId = gameId;
}

int PlayerComponentAccount::GetLastGameId() const
{
	return _lastGameId;
}
