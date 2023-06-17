#pragma once
#include "Command.h"
class SaveAs : Command
{
	MyString path;
public:
	SaveAs(const MyString& path);
	void execute(Table* t) const override;
};

