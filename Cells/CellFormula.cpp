#include "CellFormula.h"

CellFormula::CellFormula(const MyString& expression) : _expression(expression) {}

void CellFormula::parseInput(std::stringstream& ss)
{

}

double CellFormula::evaluate() const
{
	return 0;
	// go through stack and evaluate everything and add operators
}
