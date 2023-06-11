#include "CellString.h"

CellString::CellString(const MyString& value) : _value(value) {}

void CellString::printCell(size_t len, std::ostream& os) const
{
	os << _value;
	PrintHelper::printWhitespaces(len - _value.length(), os);
	os << PRINT_SEPARATOR;
}
