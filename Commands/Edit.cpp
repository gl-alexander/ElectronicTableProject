#include "Edit.h"

Edit::Edit(const MyString& cellLocation, const MyString& newValue) : cellLocation(cellLocation), newValue(newValue)
{}

void Edit::execute(Table*& table) const
{
	if(table == nullptr) throw std::logic_error("No table has been opened!");
	try
	{
		table->editCell(cellLocation, newValue);
	}
	catch (std::invalid_argument& ex)
	{
		std::cout << ex.what();
	}
}
