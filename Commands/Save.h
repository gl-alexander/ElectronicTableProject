#pragma once
#include "Command.h"
class Save : public Command
{
public:
	void execute(Table*& table) const override;
};

