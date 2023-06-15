#pragma once
#include "../Table.h"
class Command
{
protected:
public:
	Command() = default;
	virtual ~Command() = default;

	virtual void execute(Table* table) const = 0;
};

