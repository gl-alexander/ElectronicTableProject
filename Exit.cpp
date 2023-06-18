#include "Exit.h"

void Exit::execute(Table* table) const
{
	throw exit_exception();
}
