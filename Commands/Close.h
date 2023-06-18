#pragma once
#include "Command.h"
class Close : public Command
{
public:
	void execute(Table*& table) const override;
};

