#include "SaveAs.h"

SaveAs::SaveAs(const MyString& path) : path(path)
{}

void SaveAs::execute(Table*& table) const
{
	if (table == nullptr) throw std::logic_error("No table has been opened");
	try
	{
		table->saveToFile(path);
	}
	catch (std::invalid_argument& ex)
	{
		std::cout << ex.what() << std::endl;
	}
	std::cout << "File Saved Successfully!" << std::endl;
}
