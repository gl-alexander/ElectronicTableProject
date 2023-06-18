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
	catch (std::invalid_argument& ex) // invalid file name
	{
		std::cout << ex.what() << std::endl;
	}
	catch (std::runtime_error& exc) // problem with values
	{
		throw;
	}
	catch (std::logic_error& exc) // problem when parsing formulas
	{
		throw;
	}

	std::cout << "Table opened successfully!" << std::endl;
}