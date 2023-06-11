#include "CellEmpty.h"

void CellEmpty::printCell(size_t len, std::ostream& os) const
{
	PrintHelper::printWhitespaces(len, os);
	os << PRINT_SEPARATOR;
}

Cell* CellEmpty::clone() const
{
	return new CellEmpty(*this);
}
