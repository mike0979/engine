#pragma once
#include "server/component.h"
#include "server/system.h"

class PlayerComponentToken :public Component<PlayerComponentToken>, public IAwakeFromPoolSystem<std::string>
{
public:
	void Awake(const std::string token) override;
	void BackToPool() override;

	bool IsTokenValid(std::string token) const;

private:
	std::string _token;
};

