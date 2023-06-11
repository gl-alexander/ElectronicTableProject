#include "CellFraction.h"

CellFraction::CellFraction(double value) : _value(value) {}

void CellFraction::printCell(size_t len, std::ostream& os) const
{
	os.precision(PrintHelper::DECIMAL_PLACES_TO_PRINT);
	size_t valueLen = PrintHelper::doubleLen(_value, PrintHelper::DECIMAL_PLACES_TO_PRINT);
	os << _value;
	PrintHelper::printWhitespaces(len - valueLen, os);
	os << PRINT_SEPARATOR;
}
