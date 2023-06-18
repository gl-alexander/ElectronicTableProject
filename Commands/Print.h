#pragma once
#include "Command.h"
class Print : public Command
{
public:
	void execute(Table*& table) const override;
};

