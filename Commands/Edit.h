#pragma once
#include "Command.h"
class Edit : public Command
{
	MyString cellLocation;
	MyString newValue;
public:
	Edit(const MyString& cellLocation, const MyString& newValue);
	void execute(Table* table) const override;
};

