#include "Open.h"


Open::Open(const MyString& path) : path(path)
{}

void Open::execute(Table*& table) const
{
	if (table)
		throw std::logic_error("There is already an open table");

	try
	{
		table = new Table(path);
	}
	catch (std::runtime_error& exc) // problem with filename or values
	{
		std::cout << exc.what();
	}
	catch (std::logic_error& exc) // problem when parsing formulas
	{
		std::cout << exc.what();
	}
}