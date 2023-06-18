#include "Print.h"


void Print::execute(Table*& table) const
{
	if (table)
		table->print(std::cout);
	else
		throw std::logic_error("No table has been opened!");
}
