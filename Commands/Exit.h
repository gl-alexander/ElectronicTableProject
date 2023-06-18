#pragma once
#include "Command.h"
class Exit : public Command
{
public:
	void execute(Table*& table) const override;
};

