#include "CellEmpty.h"

CellEmpty::CellEmpty() : Cell(CellType::empty)
{}

void CellEmpty::printCell(size_t len, std::ostream& os) const
{
	PrintHelper::printWhitespaces(len, os);
}

Cell* CellEmpty::clone() const
{
	return new CellEmpty(*this);
}

size_t CellEmpty::getLenght() const
{
	return 0;
}

double CellEmpty::evaluate() const
{
	return 0.0;
}
