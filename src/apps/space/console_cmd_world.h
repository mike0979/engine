#pragma once
#include "server/console.h"

class ConsoleCmdWorld :public ConsoleCmd
{
public:
	void RegisterHandler() override;
	void HandleHelp() override;

protected:
	void HandleShowAllWorld(std::vector<std::string>& params);

};


