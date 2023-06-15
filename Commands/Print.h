#pragma once
#include "Command.h"
class Print : Command
{
public:
	void execute(Table* table) const override;
};

