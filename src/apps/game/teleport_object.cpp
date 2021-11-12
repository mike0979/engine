#include "teleport_object.h"

void TeleportObject::Awake(const int worldId, const uint64_t playerSn)
{
	FlagWorld.Flag = TeleportFlagType::None;
	FlagWorld.Value = 0;

	FlagPlayerSync.Flag = TeleportFlagType::None;
	FlagPlayerSync.Value = false;

	_targetWorldId = worldId;
	_playerSn = playerSn;
}

void TeleportObject::BackToPool()
{
	FlagWorld.Flag = TeleportFlagType::None;
	FlagWorld.Value = 0;

	FlagPlayerSync.Flag = TeleportFlagType::None;
	FlagPlayerSync.Value = false;

	_targetWorldId = 0;
	_playerSn = 0;
}

int TeleportObject::GetTargetWorldId() const
{
	return _targetWorldId;
}

uint64_t TeleportObject::GetPlayerSN() const
{
	return _playerSn;
}
