#include "Close.h"

void Close::execute(Table*& table) const
{
	if (table == nullptr) throw std::logic_error("No open table!");
	delete table;
	table = nullptr;
	std::cout << "File closed" << std::endl;
}
