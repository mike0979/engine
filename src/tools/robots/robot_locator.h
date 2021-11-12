#pragma once
#include "server/component.h"
#include "server/system.h"
#include "server/socket_object.h"

class Robot;

class RobotLocator :public Component<RobotLocator>, public IAwakeSystem<>
{
public:
	void Awake() override;
    void BackToPool() override;

	void RegisterToLocator(Robot* pRobot);
    bool GetRobotNetIdentify(NetIdentify* pNetIdentify);

private:
	std::mutex _lock;
	std::map<uint64_t, NetIdentify> _robots;
};

