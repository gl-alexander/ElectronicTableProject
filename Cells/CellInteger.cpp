#include "CellInteger.h"


CellInteger::CellInteger() : Cell(CellType::integer)
{}

CellInteger::CellInteger(int value) : Cell(CellType::integer), _value(value) {}

void CellInteger::printCell(size_t len, std::ostream& os) const
{
	size_t valueLen = PrintHelper::intLen(_value);
	os << _value;
	PrintHelper::printWhitespaces(len - valueLen, os);
}

void CellInteger::saveToFile(std::ofstream& ofs) const
{
	ofs << _value;
}

Cell* CellInteger::clone() const 
{
	return new CellInteger(*this);
}

size_t CellInteger::getLenght() const
{
	return PrintHelper::intLen(_value);
}

void CellInteger::setValue(int value)
{
	_value = value;
}

int CellInteger::getValue() const
{
	return _value;
}

double CellInteger::evaluate() const
{
	return _value;
}
