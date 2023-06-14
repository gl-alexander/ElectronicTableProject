#include "CellFraction.h"

CellFraction::CellFraction() : Cell(CellType::fraction) {}

CellFraction::CellFraction(double value) : Cell(CellType::fraction), _value(value) {}


void CellFraction::printCell(size_t len, std::ostream& os) const
{
	//os.precision(PrintHelper::DECIMAL_PLACES_TO_PRINT); 
	size_t valueLen = PrintHelper::doubleLen(_value);
	os << _value;
	PrintHelper::printWhitespaces(len - valueLen, os);
}

Cell* CellFraction::clone() const
{
	return new CellFraction(*this);
}

size_t CellFraction::getLenght() const
{
	return PrintHelper::doubleLen(_value);
}

void CellFraction::setValue(double value)
{
	_value = value;
}

double CellFraction::getValue() const
{
	return _value;
}

double CellFraction::evaluate() const
{
	return _value;
}

