#pragma once
#include "Command.h"
class Save : Command
{
public:
	void execute(Table* table) const override;
};

