#pragma once
#include "../Table.h"
#include <exception>

class exit_exception : public std::exception
{
public:
	const char* what() const override;
};

class Command
{
protected:
public:
	Command() = default;
	virtual ~Command() = default;

	virtual void execute(Table* table) const = 0;
};

