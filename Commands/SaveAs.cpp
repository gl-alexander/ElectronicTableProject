#include "SaveAs.h"

SaveAs::SaveAs(const MyString& path) : path(path)
{}

void SaveAs::execute(Table*& table) const
{
	if (table == nullptr) throw std::logic_error("No table has been opened");
	table->saveToFile(path);
}
