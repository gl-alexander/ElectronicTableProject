#pragma once
#include "Command.h"
class Open : Command
{
	MyString path;
public:
	Open(const MyString& path);

	void execute(Table* table) const override;

};

