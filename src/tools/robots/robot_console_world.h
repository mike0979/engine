#pragma once
#include "server/console.h"

class RobotConsoleWorld :public ConsoleCmd
{
public:
    void RegisterHandler() override;
    void HandleHelp() override;

private:
    void HandleEnter(std::vector<std::string>& params) const;
};

