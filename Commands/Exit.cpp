#include "Exit.h"

void Exit::execute(Table*& table) const
{
	delete table;
	table = nullptr;
	throw exit_exception();
}
