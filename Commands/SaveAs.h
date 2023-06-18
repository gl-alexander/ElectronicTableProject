#pragma once
#include "Command.h"
class SaveAs : public Command
{
	MyString path;
public:
	SaveAs(const MyString& path);
	void execute(Table* t) const override;
};

