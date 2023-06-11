#include "CellInteger.h"

CellInteger::CellInteger(int value) : _value(value) {}

void CellInteger::printCell(size_t len, std::ostream& os) const
{
	size_t valueLen = PrintHelper::intLen(_value);
	os << _value;
	PrintHelper::printWhitespaces(len - valueLen, os);
	os << PRINT_SEPARATOR;
}
