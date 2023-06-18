#include "Edit.h"

Edit::Edit(const MyString& cellLocation, const MyString& newValue) : cellLocation(cellLocation), newValue(newValue)
{}

void Edit::execute(Table*& table) const
{
	try
	{
		table->editCell(cellLocation, newValue);
	}
	catch (std::invalid_argument& ex)
	{
		std::cout << ex.what();
	}
}
