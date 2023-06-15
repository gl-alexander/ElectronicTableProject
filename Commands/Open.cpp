#include "Open.h"


Open::Open(const MyString& path) : path(path)
{}

void Open::execute(Table* table) const
{
	if (table)
		throw std::logic_error("There is already an open table");

	table = new Table(path);
}