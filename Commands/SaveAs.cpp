#include "SaveAs.h"

SaveAs::SaveAs(const MyString& path) : path(path)
{}

void SaveAs::execute(Table * t) const
{
	if (t == nullptr) throw std::logic_error("No table has been opened");
	t->saveToFile(path);
}
